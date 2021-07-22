from PyQt5.QtGui import*
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *

from delete_dialog import Ui_delete_dialog as Ui_Delete_Dialog
from edit_dialog import Ui_EditDialog as Ui_Edit_Dialog
from main_window import Ui_MainWindow
from add_book_dialog import Ui_Dialog as Ui_Add_dialog

import my_functions as lib

class Delete_Dialog(QDialog):
    def __init__(self, parent=None):
        super(Delete_Dialog,self).__init__(parent)
        self.ui=Ui_Delete_Dialog()
        self.ui.setupUi(self)
        self.ui.buttonBox.accepted.connect(self.accept)
        self.ui.buttonBox.rejected.connect(self.reject)

class Edit_Dialog(QDialog):
    def __init__(self, parent=None):
        super(Edit_Dialog, self).__init__(parent)
        self.ui = Ui_Edit_Dialog()
        self.ui.setupUi(self)
        self.ui.buttonBox.accepted.connect(self.accept)
        self.ui.buttonBox.rejected.connect(self.reject)

class Add_Dialog(QDialog):
    def __init__(self, parent=None):
        super(Add_Dialog,self).__init__(parent)
        self.ui = Ui_Add_dialog()
        self.ui.setupUi(self)
        self.ui.buttonBox.accepted.connect(self.accept)
        self.ui.buttonBox.rejected.connect(self.reject)

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self,parent=None):
       super(MainWindow,self).__init__(parent)
       self.setupUi(self)
       self.New_Book_Button.pressed.connect(self.show_add_dialog)
       self.load_issued_table()
       self.load_unissued_table()
       self.load_all_books_table()
       self.Edit_Issued.clicked.connect(
           lambda: self.edit_book(self.IssuedBooks_Table))
       self.Delete_Issued.pressed.connect(
            lambda: self.delete_book(self.IssuedBooks_Table)
        )
       self.Refresh_Issued.clicked.connect(self.load_issued_table)

       self.Edit_UnIssued.clicked.connect(
            lambda: self.edit_book(self.UnIssuedBooks_Table))
       self.Delete_UnIssued.pressed.connect(
            lambda: self.delete_book(self.UnIssuedBooks_Table)
        )
       self.Refresh_UnIssued.clicked.connect(self.load_unissued_table)
# comments
       self.RefreshButton.clicked.connect(self.load_all_books_table)
# search button
       self.SearchButton.clicked.connect(self.search_book)

    def save_existing_book(self, ui):
        book = {
            'id': int(ui.id_spinbox.text()),
            'name': ui.name_input.text(),
            'description': ui.description_input.text(),
            'isbn': ui.id_input_2.text(),
            'page_count': int(ui.page_count_spinbox.text()),
            'issued': ui.yes.isChecked(),
            'author': ui.author_input.text(),
            'year': int(ui.year_spinbox.text())
        }
        lib.update_book(book)

    def edit_book(self, table):
        selected_row = table.currentRow()
        if selected_row != -1:
            book_id = int(table.item(selected_row, 0).text())
            book = lib.find_book(book_id)
            # Creating the dialog
            dialog = Edit_Dialog()
            dialog.ui.id_spinbox.setValue(int(book.id))
            dialog.ui.name_input.setText(book.name)
            dialog.ui.description_input.setText(book.description)
            dialog.ui.id_input_2.setText(book.isbn)
            dialog.ui.page_count_spinbox.setValue(int(book.page_count))
            dialog.ui.yes.setChecked(book.issued)
            if book.issued == False:
                dialog.ui.no.setChecked(True)
            dialog.ui.author_input.setText(book.author)
            dialog.ui.year_spinbox.setValue(int(book.year))

            dialog.ui.buttonBox.accepted.connect(
                lambda: self.save_existing_book(dialog.ui))
            dialog.exec()
            self.load_issued_table()
            self.load_unissued_table()
    def save_new_book(self,ui):
         new_book = {
             'id': int(ui.id_spinbox.text()),
             'name': ui.name_input.text(),
             'description': ui.description_input.text(),
             'isbn': ui.id_input_2.text(),
             'page_count': ui.page_count_spinbox.text(),
             'issued':ui.yes.isChecked(),
             'author':ui.author_input.text(),
             'year': int(ui.year_spinbox.text())

             }
         for attr in new_book:
              if new_book[attr] == None or str(new_book[attr]) == "":
                    return False
         lib.add_book(new_book)
         self.load_issued_table()
         self.load_unissued_table()
         
    def search_book(self):
        if self.SearchInput.text() != "":
            book = lib.find_book(int(self.SearchInput.text()))
            if book != None:
                self.IssuedBooks_Table_2.setRowCount(1)
                book_dict = book.to_dict()

                for book_index, attr in enumerate(book_dict):
                    self.IssuedBooks_Table_2.setItem(
                        0, book_index, QTableWidgetItem(str(book_dict[str(attr)])))
                    self.IssuedBooks_Table_2.item(0, book_index).setFlags(
                        Qt.ItemIsSelectable | Qt.ItemIsEnabled)

    def load_issued_table(self):
        books = lib.get_issued_books()
        self.IssuedBooks_Table.setRowCount(len(books))
        for index, book in enumerate(books):
            book = book.to_dict()
            for book_index, attr in enumerate(book):
                self.IssuedBooks_Table.setItem(
                    index, book_index, QTableWidgetItem(str(book[str(attr)])))
                self.IssuedBooks_Table.item(index, book_index).setFlags(
                    Qt.ItemIsSelectable | Qt.ItemIsEnabled)

    def delete_book(self, table):
        selected_row = table.currentRow()
        if selected_row != -1:
            book_id = int(table.item(selected_row, 0).text())
            dialog = Delete_Dialog()
            dialog.ui.buttonBox.accepted.connect(
                lambda: lib.delete_book(book_id)
            )

            dialog.exec()
            self.load_issued_table()
            self.load_unissued_table()

    def load_unissued_table(self):
         books = lib.get_unissued_books()
         self.UnIssuedBooks_Table.setRowCount(len(books))
         for index, book in enumerate(books):
             book = book.to_dict()
             for book_index, attr in enumerate(book):
                   self.UnIssuedBooks_Table.setItem(
                   index, book_index, QTableWidgetItem(str(book[str(attr)])))
                   self.UnIssuedBooks_Table.item(index, book_index).setFlags(
                     Qt.ItemIsSelectable | Qt.ItemIsEnabled)

    def load_all_books_table(self):
        books = lib.load_books()
        self.All_Books_Table.setRowCount(len(books))
        for index, book in enumerate(books):
            book = book.to_dict()
            for book_index, attr in enumerate(book):
                self.All_Books_Table.setItem(
                    index, book_index, QTableWidgetItem(str(book[str(attr)])))
                self.All_Books_Table.item(index, book_index).setFlags(
                    Qt.ItemIsSelectable | Qt.ItemIsEnabled)

    def show_add_dialog(self):
        input_dlg = Add_Dialog()
        input_dlg.ui.buttonBox.accepted.connect(lambda: self.save_new_book(input_dlg.ui))
        input_dlg.exec()

app = QApplication([])
window = MainWindow()
window.show()
app.exec()
