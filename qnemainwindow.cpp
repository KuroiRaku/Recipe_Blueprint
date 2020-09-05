/* Copyright (c) 2012, STANISLAW ADASZEWSKI
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STANISLAW ADASZEWSKI nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL STANISLAW ADASZEWSKI BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#include "qnemainwindow.h"
#include "ui_qnemainwindow.h"

#include "qneblock.h"
#include "qnodeseditor.h"

#include <QGraphicsScene>
#include <QFileDialog>

#include "qneport.h"

QNEMainWindow::QNEMainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::QNEMainWindow)
{
    scene = new QGraphicsScene();




    //setting up ui that we use in ui_qnemainwindow.h
    //I was thinking abstracting UI into a class, but lets do in the same class instead
    //ui->setupUi(this);
    createMenu();

    QWidget *centralWidget = new QWidget(this);
    this->setCentralWidget(centralWidget);

    setWindowTitle(tr("Recipe Blueprint"));



    QDockWidget *dock = new QDockWidget(tr("Nodes"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    view = new QGraphicsView(dock);
    view->setScene(scene);

    view->setRenderHint(QPainter::Antialiasing, true);

    dock->setWidget(view);
    addDockWidget(Qt::LeftDockWidgetArea, dock);



    nodesEditor = new QNodesEditor(this);
    nodesEditor->install(scene);


    //addFryingProcesses();

    QNEBlock *b = new QNEBlock(0);
    scene->addItem(b);
    b->addPort("random", 0, QNEPort::NamePort);
    b->addPort("random block", 0, QNEPort::TypePort);
    b->addInputPort("in1");
    b->addInputPort("in2");
    b->addInputPort("in3");
    b->addOutputPort("out1");
    b->addOutputPort("out2");
    b->addOutputPort("out3");

    b = b->clone();
    b->setPos(150, 0);

    b = b->clone();
    b->setPos(150, 150);


}

QNEMainWindow::~QNEMainWindow()
{
    delete ui;
}

void QNEMainWindow::saveFile()
{
	QString fname = QFileDialog::getSaveFileName();
	if (fname.isEmpty())
		return;

	QFile f(fname);
	f.open(QFile::WriteOnly);
	QDataStream ds(&f);
	nodesEditor->save(ds);
}

void QNEMainWindow::loadFile()
{
	QString fname = QFileDialog::getOpenFileName();
	if (fname.isEmpty())
		return;

	QFile f(fname);
	f.open(QFile::ReadOnly);
	QDataStream ds(&f);
	nodesEditor->load(ds);
}

void QNEMainWindow::addBlock()
{
    QNEBlock *b = new QNEBlock(0);

    scene->addItem(b);
    static const char* names[] = {"Fry", "Voutsadfasdf", "Imin", "Imax", "mul", "add", "sub", "div", "Conv", "FFT"};
	for (int i = 0; i < 4 + rand() % 3; i++)
	{
		b->addPort(names[rand() % 10], rand() % 2, 0, 0);
        b->setPos(view->sceneRect().center().toPoint());
	}
}

void QNEMainWindow::addFryingProcesses()
{
    QNEBlock *b = new QNEBlock(0);
    scene->addItem(b);
    b->addPort("Frying", 0, QNEPort::NamePort);
    b->addPort("Processes", 0, QNEPort::TypePort);

    b->addInputPort("in1 Ingredient");
    b->addInputPort("in2 Ingredient");
    b->addInputPort("in3 Utensils");
    b->addOutputPort("out1");
    b->setPos(QCursor::pos());

}

void QNEMainWindow::addDescription()
{
    QNEBlock *b = new QNEBlock(0);
    scene->addItem(b);
    b->addPort("Description", 0, QNEPort::NamePort);
    b->addPort("Remember to season it!", 0, QNEPort::DescriptionPort);
    b->setPos(QCursor::pos());
}


void QNEMainWindow::addIngredient()
{
    QNEBlock *b = new QNEBlock(0);
    scene->addItem(b);
    b->addPort("User Input", 0, QNEPort::TextInputPort);
    b->addPort("Ingredient", 0, QNEPort::TypePort);

    b->addOutputPort("out1");
    b->setPos(QCursor::pos());
}

void QNEMainWindow::createMenu()
{

    QAction *quitAct = new QAction(tr("&Quit"), this);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));
    connect(quitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    QAction *loadAct = new QAction(tr("&Load"), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Open a file"));
    connect(loadAct, SIGNAL(triggered()), this, SLOT(loadFile()));

    QAction *saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save a file"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    QAction *addAct = new QAction(tr("&Add"), this);
    addAct->setStatusTip(tr("Add a block"));
    connect(addAct, SIGNAL(triggered()), this, SLOT(addBlock()));



    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addAct);
    fileMenu->addAction(loadAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);

}

void QNEMainWindow::cut()
{
    //infoLabel->setText(tr("Invoked <b>Edit|Cut</b>"));
}

void QNEMainWindow::copy()
{
    //infoLabel->setText(tr("Invoked <b>Edit|Copy</b>"));
}

void QNEMainWindow::paste()
{
    //infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void QNEMainWindow::redo()
{
    //infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

void QNEMainWindow::undo()
{
    //infoLabel->setText(tr("Invoked <b>Edit|Paste</b>"));
}

#ifndef QT_NO_CONTEXTMENU
void QNEMainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    QAction *cutAct = new QAction(tr("&Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut"));
    connect(cutAct, SIGNAL(triggered()), this, SLOT(cut()));
    menu.addAction(cutAct);

    QAction *copyAct = new QAction(tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy"));
    connect(copyAct, SIGNAL(triggered()), this, SLOT(copy()));
    menu.addAction(copyAct);

    QAction *pasteAct = new QAction(tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste"));
    connect(pasteAct, SIGNAL(triggered()), this, SLOT(paste()));
    menu.addAction(pasteAct);

    QAction *addIngredient = new QAction(tr("&AddIngredient"), this);
    addIngredient->setStatusTip(tr("Save a file"));
    connect(addIngredient, SIGNAL(triggered()), this, SLOT(addIngredient()));
    menu.addAction(addIngredient);

    QAction *addProcesses = new QAction(tr("&AddProcesses"), this);
    addProcesses->setStatusTip(tr("Add Processes"));
    connect(addIngredient, SIGNAL(triggered()), this, SLOT(addFryingProcesses()));
    menu.addAction(addProcesses);

    QAction *addDescription = new QAction(tr("&AddDescription"), this);
    addProcesses->setStatusTip(tr("Add Description"));
    connect(addIngredient, SIGNAL(triggered()), this, SLOT(addDescription()));
    menu.addAction(addDescription);







    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU
