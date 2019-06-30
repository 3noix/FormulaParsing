#include "MainWindow.h"
#include "ExceptionInterpreter.h"
#include "TextEdit.h"
#include <QVBoxLayout>
#include <QLineEdit>


///////////////////////////////////////////////////////////////////////////////
//  CONSTRUCTEUR
//
//  CREATE ACTIONS
//  CREATE MENUS
//  CREATE TOOLBAR
//  SETUP WIDGET
//
//  SLOT COMPUTE
///////////////////////////////////////////////////////////////////////////////


// CONSTRUCTEUR ///////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent}
{
	this->createActions();
	this->createMenus();
	this->createToolBar();
	this->setupWidget();
	
	// connections
	QObject::connect(lineCommand, &QLineEdit::returnPressed, this, &MainWindow::slotCompute);
	
	// end
	lineCommand->setFocus(Qt::OtherFocusReason);
}






// CREATE ACTIONS /////////////////////////////////////////////////////////////
void MainWindow::createActions()
{
}

// CREATE MENUS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createMenus()
{
}

// CREATE TOOLBAR //////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::createToolBar()
{
}

// SETUP WIDGET ///////////////////////////////////////////////////////////////
void MainWindow::setupWidget()
{
	// main widget and layout
	mainWidget = new QWidget{this};
	layout = new QVBoxLayout{mainWidget};
	mainWidget->setLayout(layout);
	this->setCentralWidget(mainWidget);
	
	textEdit = new TextEdit{this};
	lineCommand = new QLineEdit{this};
	
	layout->addWidget(textEdit);
	layout->addWidget(lineCommand);
	
	// end
	this->resize(600,500);
	//this->setWindowIcon(QIcon{":/RESOURCES/ICONES/gamepad.png"});
	this->setWindowTitle("Formula interpreter");
}






// SLOT COMPUTE ///////////////////////////////////////////////////////////////
void MainWindow::slotCompute()
{
	QString formula = lineCommand->text().trimmed();
	lineCommand->clear();
	if (formula.isEmpty()) {return;}
	textEdit->slotAddMessage(">> "+formula,Qt::black);
	
	// formula preration
	QStringList prepErrors;
	bool bPrepa = m_interpreter.prepare(formula,&prepErrors);
	if (!bPrepa)
	{
		for (const QString &error : prepErrors) {textEdit->slotAddMessage(error,Qt::red);}
		return;
	}
	
	// formula computation
	try
	{
		Any result = m_interpreter.eval(formula);
		textEdit->slotAddMessage(::toString(result),Qt::black);
	}
	catch (const ExceptionInterpreter &e)
	{
		textEdit->slotAddMessage(e.text(),Qt::red);
	}
}

