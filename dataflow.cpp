#include "dataflow.h"

#include "QuickQanava.h"


namespace qan { // ::qan

void    FlowNodeBehaviour::inNodeInserted( qan::Node& inNode, qan::Edge& edge ) noexcept
{
    Q_UNUSED(edge);
    const auto inFlowNode = qobject_cast<qan::FlowNode*>(&inNode);
    const auto flowNodeHost = qobject_cast<qan::FlowNode*>(getHost());
    if ( inFlowNode != nullptr &&
         flowNodeHost != nullptr ) {
        //
        QObject::connect(inFlowNode,    &qan::FlowNode::outputChanged,
                         flowNodeHost,  &qan::FlowNode::inNodeOutputChanged);
    }
    flowNodeHost->inNodeOutputChanged();    // Force a call since with a new edge insertion, actual value might aready be initialized
}

void    FlowNodeBehaviour::inNodeRemoved( qan::Node& inNode, qan::Edge& edge ) noexcept
{
    Q_UNUSED(inNode); Q_UNUSED(edge);
}

QQmlComponent*  FlowNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   qan_FlowNode_delegate;
    if ( !qan_FlowNode_delegate )
        qan_FlowNode_delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/FlowNode.qml");
    return qan_FlowNode_delegate.get();
}

void    FlowNode::inNodeOutputChanged()
{

}

void    FlowNode::setOutput(QVariant output) noexcept
{
    _output = output;
    emit outputChanged();
}

QQmlComponent*  PercentageNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/PercentageNode.qml");
    return delegate.get();
}

QQmlComponent*  ProcessesNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/Processes.qml");
    return delegate.get();
}

void    ProcessesNode::setOperation(Operation operation) noexcept
{
    if ( _operation != operation ) {
        _operation = operation;
        emit operationChanged();
    }
}

void    ProcessesNode::inNodeOutputChanged()
{
    FlowNode::inNodeOutputChanged();
    qreal o{0.}; // For the example sake we do not deal with overflow
    bool oIsInitialized{false};
    for ( const auto& inNode : get_in_nodes() ) {
        const auto inFlowNode = qobject_cast<qan::FlowNode*>(inNode.lock().get());
        if ( inFlowNode == nullptr ||
             !inFlowNode->getOutput().isValid())
            continue;
        bool ok{false};
        const auto inOutput = inFlowNode->getOutput().toReal(&ok);
        if ( ok ) {
            switch ( _operation ) {
            case Operation::Add:
                o += inOutput;
                break;
            case Operation::Multiply:
                if ( !oIsInitialized ) {
                    o = inOutput;
                    oIsInitialized = true;
                } else
                    o *= inOutput;
                break;
            }
        }
    }
    setOutput(o);
}

QQmlComponent*  ImageNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/ImageNode.qml");
    return delegate.get();
}

QQmlComponent*  IngredientNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/Ingredient.qml");
    return delegate.get();
}

QQmlComponent*  TintNode::delegate(QQmlEngine& engine) noexcept
{
    static std::unique_ptr<QQmlComponent>   delegate;
    if ( !delegate )
        delegate = std::make_unique<QQmlComponent>(&engine, "qrc:/TintNode.qml");
    return delegate.get();
}

void    TintNode::setSource(QUrl source) noexcept
{
    if ( _source != source ) {
        _source = source;
        emit sourceChanged();
    }
}

void    TintNode::setTintColor(QColor tintColor) noexcept
{
    if ( _tintColor != tintColor ) {
        _tintColor = tintColor;
        emit tintColorChanged();
    }
}

void    TintNode::inNodeOutputChanged()
{
    FlowNode::inNodeOutputChanged();
    qDebug() << "TintNode::inNodeOutputValueChanged()";
    if ( get_in_nodes().size() != 3 )
        return;

    // FIXME: Do not find port item by index, but by id with qan::NodeItem::findPort()...

    const auto inFactorNode = qobject_cast<qan::FlowNode*>(get_in_nodes().at(0).lock().get());
    const auto inColorNode = qobject_cast<qan::FlowNode*>(get_in_nodes().at(1).lock().get());
    const auto inImageNode = qobject_cast<qan::FlowNode*>(get_in_nodes().at(2).lock().get());
    qDebug() << "inFactorNode=" << inFactorNode << "\tinColorNode=" << inColorNode << "\tinImageNode=" << inImageNode;
    if ( inFactorNode == nullptr ||
         inColorNode == nullptr ||
         inImageNode == nullptr )
        return;
    bool factorOk{false};
    const auto factor = inFactorNode->getOutput().toReal(&factorOk);
    auto       tint =   inColorNode->getOutput().value<QColor>();
    const auto source = inImageNode->getOutput().toUrl();
    qDebug() << "factor=" << factor;
    qDebug() << "tint=" << tint;
    qDebug() << "source=" << source.toString();
    if ( factorOk &&
         !source.isEmpty() &&
         tint.isValid() ) {
        tint.setAlpha(qBound(0., factor, 1.0) * 255);
        setSource(source);
        setTintColor(tint);
    }
}

qan::Node* FlowGraph::insertFlowNode(FlowNode::Type type)
{
    qan::Node* flowNode = nullptr;
    switch ( type ) {
    case qan::FlowNode::Type::Percentage:
        flowNode = insertNode<PercentageNode>(nullptr);
        insertPort(flowNode, qan::NodeItem::Dock::Right, qan::PortItem::Type::Out, "OUT", "OUT" );
        break;
    case qan::FlowNode::Type::Image:
        flowNode = insertNode<ImageNode>(nullptr);
        insertPort(flowNode, qan::NodeItem::Dock::Right, qan::PortItem::Type::Out, "OUT", "OUT" );
        break;
    case qan::FlowNode::Type::Operation: {
        flowNode = insertNode<ProcessesNode>(nullptr);
        // Insert out port first we need to modify it from ProcessesNode.qml delegate
        insertPort(flowNode, qan::NodeItem::Dock::Right, qan::PortItem::Type::Out, "OUT", "OUT" );

        // In ports should have Single multiplicity: only one value (ie one input edge) binded to a port
        const auto inp1 = insertPort(flowNode, qan::NodeItem::Dock::Left, qan::PortItem::Type::In, "IN", "IN1" );
        inp1->setMultiplicity(qan::PortItem::Multiplicity::Single);
        const auto inp2 = insertPort(flowNode, qan::NodeItem::Dock::Left, qan::PortItem::Type::In, "IN", "IN2" );
        inp2->setMultiplicity(qan::PortItem::Multiplicity::Single);
    }
        break;
    case qan::FlowNode::Type::Color:
        flowNode = insertNode<ColorNode>(nullptr);
        insertPort(flowNode, qan::NodeItem::Dock::Right, qan::PortItem::Type::Out, "OUT", "OUT" );
        break;
    case qan::FlowNode::Type::Tint:
        flowNode = insertNode<TintNode>(nullptr);
        insertPort(flowNode, qan::NodeItem::Dock::Left, qan::PortItem::Type::In, "FACTOR", "FACTOR" );
        insertPort(flowNode, qan::NodeItem::Dock::Left, qan::PortItem::Type::In, "COLOR", "COLOR" );
        insertPort(flowNode, qan::NodeItem::Dock::Left, qan::PortItem::Type::In, "IMAGE", "IMAGE" );
        break;
    default: return nullptr;
    }
    if ( flowNode )
        flowNode->installBehaviour(std::make_unique<FlowNodeBehaviour>());
    return flowNode;
}

} // ::qan

