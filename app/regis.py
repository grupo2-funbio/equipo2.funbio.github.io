import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QDialog, QApplication
from PyQt5.uic import loadUi

class Login(QDialog):
    def __init__(self):
        super(Login,self).__init__()
        loadUi("login.ui",self)
        self.botonlogin.clicked.connect(self.loginfunction)
        self.createaccbutton.clicked.connect(self.gotocreate)

    def loginfunction(self):
        registro=CreateAcb()
        widget.addWidget(registro)
        widget.setCurrentIndex(widget.currentIndex()+1)

    def gotocreate(self):
        createacc=CreateAcc()
        widget.addWidget(createacc)
        widget.setCurrentIndex(widget.currentIndex()+1)
        

class CreateAcc(QDialog):
    def __init__(self):
        super(CreateAcc,self).__init__()
        loadUi("createacc.ui",self)
        self.signupbutton.clicked.connect(self.gotomenu)
    def gotomenu(self):
        menu=CreateAdd()
        widget.addWidget(menu)
        widget.setCurrentIndex(widget.currentIndex()+1)

class CreateAcb(QDialog):
    def __init__(self):
        super(CreateAcb,self).__init__()
        loadUi("registro.ui",self)
        self.importboton.clicked.connect(self.gotodatos)
    def gotodatos(self):
        datos=CreateAbb()
        widget.addWidget(datos)
        widget.setCurrentIndex(widget.currentIndex()+1)

class CreateAbb(QDialog):
    def __init__(self):
        super(CreateAbb,self).__init__()
        loadUi("datos.ui",self)

class CreateAdd(QDialog):
    def __init__(self):
        super(CreateAdd,self).__init__()
        loadUi("login.ui",self)
        self.botonlogin.clicked.connect(self.loginfunction)
        self.createaccbutton.clicked.connect(self.gotocreate)
        
    def loginfunction(self):
        registro=CreateAcb()
        widget.addWidget(registro)
        widget.setCurrentIndex(widget.currentIndex()+1)

    def gotocreate(self):
        createacc=CreateAcc()
        widget.addWidget(createacc)
        widget.setCurrentIndex(widget.currentIndex()+1)


        

app=QApplication(sys.argv)
mainwindow=Login()
widget=QtWidgets.QStackedWidget()
widget.addWidget(mainwindow)
widget.setFixedWidth(480)
widget.setFixedHeight(620)
widget.show()
app.exec_()