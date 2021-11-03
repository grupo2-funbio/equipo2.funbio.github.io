import sys
from PyQt5 import QtWidgets
from PyQt5.QtWidgets import QDialog, QApplication
from PyQt5.uic import loadUi

class Login(QDialog):
    def __init__(self):
        super(Login,self).__init__()
        loadUi("login.ui",self)
        self.botonlogin.clicked.connect(self.loginfunction)
        self.contra.setEchoMode(QtWidgets.QLineEdit.contra)
        self.createaccbutton.clicked.connect(self.gotocreate)

    def loginfunction(self):
        email=self.email.text()
        contra=self.contra.text()
        print("Successfully logged in with email: ", email, "and contra:", contra)

    def gotocreate(self):
        createacc=CreateAcc()
        widget.addWidget(createacc)
        widget.setCurrentIndex(widget.currentIndex()+1)

class CreateAcc(QDialog):
    def __init__(self):
        super(CreateAcc,self).__init__()
        loadUi("createacc.ui",self)
        self.signupbutton.clicked.connect(self.createaccfunction)
        self.contra.setEchoMode(QtWidgets.QLineEdit.contra)
        self.confirmpass.setEchoMode(QtWidgets.QLineEdit.contra)

    def createaccfunction(self):
        usuario = self.usuario.text()
        if self.contra.text()==self.confirmpass.text():
            contra=self.contra.text()
            print("Successfully created acc with usuario: ", usuario, "and contra: ", contra)
            login=Login()
            widget.addWidget(login)
            widget.setCurrentIndex(widget.currentIndex()+1)



app=QApplication(sys.argv)
mainwindow=Login()
widget=QtWidgets.QStackedWidget()
widget.addWidget(mainwindow)
widget.setFixedWidth(480)
widget.setFixedHeight(620)
widget.show()
app.exec_()