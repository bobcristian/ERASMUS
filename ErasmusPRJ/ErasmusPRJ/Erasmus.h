#pragma once
#include "AddStudent.h"
#include "UpdateStudent.h"
#include "AddCatalog.h"
#include "UpdateCatalog.h"
#include "AddUniversitate.h"
#include "UpdateUniversitate.h"
#include "AddTara.h"
#include "UpdateTara.h"
#include "ServerCredentials.h"
#include "ResetPassword.h"

namespace ErasmusPRJ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	/// <summary>
	/// Summary for Erasmus
	/// </summary>
	public ref class Erasmus : public System::Windows::Forms::Form
	{
	public:
		Erasmus(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			ShowComboBox->Text = "Elevi";
		}

		Erasmus(System::Windows::Forms::Form^ newForm,String^ user)
		{
			InitializeComponent();
			ShowComboBox->Text = "Elevi";
			userName = user;
			loginForm = newForm;
			if (userName->Equals("Guest"))
			{
				FadeComponents();
			}
			else
			{
				WriteUser();
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Erasmus()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^  EleviDataGrid;
	private: System::Windows::Forms::Button^  DeleteButton;
	private: System::Windows::Forms::Button^  AddButton;
	private: System::Windows::Forms::Button^  EditButton;
	private: System::Windows::Forms::ComboBox^  ShowComboBox;
	private: System::Windows::Forms::GroupBox^  ShowGroupBox;

	private: System::Windows::Forms::GroupBox^  SearchGroupBox;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  FileMenu;
	private: System::Windows::Forms::ToolStripTextBox^  PrintOption;
	private: System::Windows::Forms::ToolStripMenuItem^  OptionsMenu;
	private: System::Windows::Forms::ToolStripTextBox^  ResetPasswordOption;
	private: System::Windows::Forms::ToolStripTextBox^  ServerCredentialsOption;
	private: System::Windows::Forms::ToolStripTextBox^  LoginFormOption;



	public: System::Windows::Forms::Button^  ShowButton;
	private:

	protected:
		void ShowInDataGrid(MySqlCommand^ cmdDataBase)
		{
			try {
				MySqlDataAdapter^ sda = gcnew MySqlDataAdapter();
				sda->SelectCommand = cmdDataBase;
				DataTable^ dbDataSet = gcnew DataTable();
				sda->Fill(dbDataSet);
				BindingSource^ bSource = gcnew BindingSource();

				bSource->DataSource = dbDataSet;
				EleviDataGrid->DataSource = bSource;
				sda->Update(dbDataSet);
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
			}
		}

		void removeFromCourses(String^ studentID)
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			//Variabile{
			studentID = studentID + "/";
			array<String^>^ studCatalog = gcnew array<String^>(100);
			String^ studToRemove = "";
			int course[20];
			int n = 0;
			int index;
			bool found;
			//}
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.catalog;", conDataBase);
			MySqlDataReader^ myReader;

			try {
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();

				while (myReader->Read())
				 {
					studToRemove = myReader->GetString("Studenti");
					found = studToRemove->Contains(studentID);
					if (found)
					{
						index = studToRemove->IndexOf(studentID);
						studCatalog[n] = studToRemove->Remove(index, 3);
						course[n++] = myReader->GetInt32("ID");
					}	//retine cursurile la care e inscris studentul si ii sterge ID-ul
				 }
				}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
			conDataBase->Close();
			myReader->Close();
			//se inchice prima conexiune

			conDataBase->Open();//se deschide conexiunea pentru a updata baza de date
			MySqlDataReader^ update;
			for (int i = 0; i < n; i++) {
				try
				{
					MySqlCommand^ updateDataBase = gcnew MySqlCommand("update erasmus.catalog SET Studenti='" + studCatalog[i] + "' where ID=" + course[i] + ";",conDataBase);
					update = updateDataBase->ExecuteReader();
					update->Read();
					update->Close();//se inchide reader-ul
				}
				catch (Exception^ ex)
				{
					MessageBox::Show(ex->Message);
				}
			}//for pentru a parcurge toate cursurile la care e inscris studentul care trebuie sters;
		}

		void addElev()
		{
			AddStudent^ addStudent = gcnew AddStudent();
			addStudent->Show();
		}

		void updateElev()
		{
			if (EleviDataGrid->SelectedRows->Count > 0) {
				int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
				String^ toEdit = EleviDataGrid->Rows[rowIndex]->Cells["ID"]->Value->ToString();
				UpdateStudent^ updateStud = gcnew UpdateStudent(toEdit, this);
				updateStud->Show();
				ShowButton->PerformClick();
			}
		}

		void deleteElev()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			if (EleviDataGrid->SelectedRows->Count > 0) {
				int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
				String^ toDelete = EleviDataGrid->Rows[rowIndex]->Cells["ID"]->Value->ToString();
				removeFromCourses(toDelete);
				MySqlCommand^ cmdDataBase = gcnew MySqlCommand("delete from erasmus.elevi where ID='" + toDelete + "';", conDataBase);
				MySqlDataReader^ myReader;

				try {
					conDataBase->Open();
					myReader = cmdDataBase->ExecuteReader();
					while (myReader->Read())
					{

					}
				}
				catch (Exception^ ex)
				{
					MessageBox::Show(ex->Message);
				}
			}
			ShowButton->PerformClick();
		}
		
		void addCatalog()
		{
			AddCatalog^ addCatalog = gcnew AddCatalog();
			addCatalog->Show();
		}

		void removeCourses(String^ courseName)//+imbunatatire: accesare studenti dupa campul Studenti
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ selectDataBase = gcnew MySqlCommand("select * from erasmus.elevi;", conDataBase);
			MySqlDataReader^ myReader;
			//Variabile
			bool found;
			int index;
			int elevi[80];
			array<String^>^ catalog = gcnew array<String^>(80);
			int n = 0;
			String^ courses;
			//

			courseName = courseName + "/";
			try
			{
				conDataBase->Open();
				myReader = selectDataBase->ExecuteReader();
				while (myReader->Read())
				{
					courses = myReader->GetString("Catalog");
					found = courses->Contains(courseName);
					if (found)
					{
						index = courses->IndexOf(courseName);
						catalog[n] = courses->Remove(index, courseName->Length);
						elevi[n++] = myReader->GetInt32("ID");
					}//salveaza elevii care sunt inscrisi la cursul respectiv
				}
				conDataBase->Close();
				myReader->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}

			conDataBase->Open();
			MySqlDataReader^ update;
			for (int i = 0; i < n; i++)
			{
				try
				{
					MySqlCommand^ updateDataBase = gcnew MySqlCommand("update erasmus.elevi SET Catalog='" + catalog[i] + "' where ID=" + elevi[i] + ";", conDataBase);
					update = updateDataBase->ExecuteReader();
					update->Read();
					update->Close();
				}//sterge cursul respectiv de la elevi
				catch (Exception^ ex)
				{
					MessageBox::Show(ex->Message);
				}
			}
			conDataBase->Close();

		}

		void deleteCatalog()
		{
			if (MessageBox::Show("Acest curs va fi sters de la toti studentii. Sunteti sigur ca vreti sa continuati?",
				"Delete Course", MessageBoxButtons::YesNo,
				MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
				MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
				if (EleviDataGrid->SelectedRows->Count > 0) {
					int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
					String^ toDelete = EleviDataGrid->Rows[rowIndex]->Cells["Nume_curs"]->Value->ToString();
					MySqlCommand^ delDataBase = gcnew MySqlCommand("delete from erasmus.catalog where Nume_curs='" + toDelete + "';", conDataBase);
					MySqlDataReader^ myReader;
					removeCourses(toDelete);

					try
					{
						conDataBase->Open();
						myReader = delDataBase->ExecuteReader();
						myReader->Read();
					}
					catch(Exception^ ex)
					{
						MessageBox::Show(ex->Message);
					}
				}//Inchide al doilea if
				ShowButton->PerformClick();
			}//Inchide if-ul
		}

		void updateCatalog()
		{
			if (EleviDataGrid->SelectedRows->Count > 0)
			{
				int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
				int idToEdit = System::Convert::ToInt32(EleviDataGrid->Rows[rowIndex]->Cells["ID"]->Value->ToString());
				String^ nameToEdit = EleviDataGrid->Rows[rowIndex]->Cells["Nume_curs"]->Value->ToString();
				UpdateCatalog^ updateCatalog = gcnew UpdateCatalog(idToEdit,nameToEdit);
				updateCatalog->Show();
			}
		}

		void addUniversitate()
		{
			AddUniversitate^ addUniversitate = gcnew AddUniversitate();
			addUniversitate->Show();
		}

		void deleteUniversitate()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			if (EleviDataGrid->SelectedRows->Count > 0) {
				int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
				String^ toDelete = EleviDataGrid->Rows[rowIndex]->Cells["ID"]->Value->ToString();
				MySqlCommand^ cmdDataBase = gcnew MySqlCommand("delete from erasmus.universitati where ID='" + toDelete + "';", conDataBase);
				MySqlDataReader^ myReader;

				try {
					conDataBase->Open();
					myReader = cmdDataBase->ExecuteReader();
					while (myReader->Read())
					{

					}
				}
				catch (Exception^ ex)
				{
					MessageBox::Show(ex->Message);
				}
			}
			ShowButton->PerformClick();
		}

		void updateUni()
		{
			if (EleviDataGrid->SelectedRows->Count > 0) {
				int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
				String^ toEdit = EleviDataGrid->Rows[rowIndex]->Cells["ID"]->Value->ToString();
				UpdateUniversitate^ updateUniversitate = gcnew UpdateUniversitate(toEdit);
				updateUniversitate->Show();
			}
		}

		void addTara()
		{
			AddTara^ addTara = gcnew AddTara();
			addTara->Show();
		}

		void deleteTara()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			if (EleviDataGrid->SelectedRows->Count > 0) {
				int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
				String^ toDelete = EleviDataGrid->Rows[rowIndex]->Cells["ID"]->Value->ToString();
				MySqlCommand^ cmdDataBase = gcnew MySqlCommand("delete from erasmus.tari where ID='" + toDelete + "';", conDataBase);
				MySqlDataReader^ myReader;

				try {
					conDataBase->Open();
					myReader = cmdDataBase->ExecuteReader();
					while (myReader->Read())
					{

					}
				}
				catch (Exception^ ex)
				{
					MessageBox::Show(ex->Message);
				}
			}
			ShowButton->PerformClick();
		}

		void updateTara()
		{
			if (EleviDataGrid->SelectedRows->Count > 0) {
				int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
				String^ toEdit = EleviDataGrid->Rows[rowIndex]->Cells["ID"]->Value->ToString();
				UpdateTara^ updateTara = gcnew UpdateTara(toEdit);
				updateTara->Show();
			}
		}

		void FadeComponents()
		{
			AddButton->Enabled = false;
			DeleteButton->Enabled = false;
			EditButton->Enabled = false;
			ResetPasswordOption->Enabled = false;
			ServerCredentialsOption->Enabled = false;
		}

		void WriteUser()
		{
			String^ fileName = "User.txt";
			StreamWriter^ sw = gcnew StreamWriter(fileName);
			sw->Write(userName);
			sw->Close();
		}

	private: String^ conString = L"datasource=localhost;port=3306;username=root;password=bobcrisaudir8;";
	private: System::Windows::Forms::TextBox^  SearchStudentTextBox;
	private: System::Windows::Forms::Button^  SearchButton;
		/// <summary>
		String^ option = "";
		String^ userName;
		System::Windows::Forms::Form^ loginForm;
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Erasmus::typeid));
			this->EleviDataGrid = (gcnew System::Windows::Forms::DataGridView());
			this->ShowButton = (gcnew System::Windows::Forms::Button());
			this->SearchStudentTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SearchButton = (gcnew System::Windows::Forms::Button());
			this->DeleteButton = (gcnew System::Windows::Forms::Button());
			this->AddButton = (gcnew System::Windows::Forms::Button());
			this->EditButton = (gcnew System::Windows::Forms::Button());
			this->ShowComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->ShowGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->SearchGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->FileMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->PrintOption = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->OptionsMenu = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ResetPasswordOption = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->ServerCredentialsOption = (gcnew System::Windows::Forms::ToolStripTextBox());
			this->LoginFormOption = (gcnew System::Windows::Forms::ToolStripTextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EleviDataGrid))->BeginInit();
			this->ShowGroupBox->SuspendLayout();
			this->SearchGroupBox->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// EleviDataGrid
			// 
			this->EleviDataGrid->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->EleviDataGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->EleviDataGrid->Location = System::Drawing::Point(149, 68);
			this->EleviDataGrid->Name = L"EleviDataGrid";
			this->EleviDataGrid->Size = System::Drawing::Size(760, 454);
			this->EleviDataGrid->TabIndex = 0;
			// 
			// ShowButton
			// 
			this->ShowButton->Location = System::Drawing::Point(23, 69);
			this->ShowButton->Name = L"ShowButton";
			this->ShowButton->Size = System::Drawing::Size(85, 34);
			this->ShowButton->TabIndex = 1;
			this->ShowButton->Text = L"Show/Refresh";
			this->ShowButton->UseVisualStyleBackColor = true;
			this->ShowButton->Click += gcnew System::EventHandler(this, &Erasmus::ShowButton_Click);
			// 
			// SearchStudentTextBox
			// 
			this->SearchStudentTextBox->BackColor = System::Drawing::SystemColors::Window;
			this->SearchStudentTextBox->ForeColor = System::Drawing::SystemColors::ControlText;
			this->SearchStudentTextBox->Location = System::Drawing::Point(44, 8);
			this->SearchStudentTextBox->Name = L"SearchStudentTextBox";
			this->SearchStudentTextBox->Size = System::Drawing::Size(147, 20);
			this->SearchStudentTextBox->TabIndex = 2;
			this->SearchStudentTextBox->Text = L"Search student here...";
			this->SearchStudentTextBox->Click += gcnew System::EventHandler(this, &Erasmus::SearchStudentTextBox_Click);
			this->SearchStudentTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Erasmus::SearchStudentTextBox_KeyDown);
			this->SearchStudentTextBox->Leave += gcnew System::EventHandler(this, &Erasmus::SearchStudentTextBox_Leave);
			// 
			// SearchButton
			// 
			this->SearchButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SearchButton.Image")));
			this->SearchButton->Location = System::Drawing::Point(7, 2);
			this->SearchButton->Name = L"SearchButton";
			this->SearchButton->Size = System::Drawing::Size(31, 31);
			this->SearchButton->TabIndex = 3;
			this->SearchButton->UseVisualStyleBackColor = true;
			this->SearchButton->Click += gcnew System::EventHandler(this, &Erasmus::SearchButton_Click);
			// 
			// DeleteButton
			// 
			this->DeleteButton->Location = System::Drawing::Point(36, 80);
			this->DeleteButton->Name = L"DeleteButton";
			this->DeleteButton->Size = System::Drawing::Size(81, 27);
			this->DeleteButton->TabIndex = 4;
			this->DeleteButton->Text = L"Delete";
			this->DeleteButton->UseVisualStyleBackColor = true;
			this->DeleteButton->Click += gcnew System::EventHandler(this, &Erasmus::DeleteButton_Click);
			// 
			// AddButton
			// 
			this->AddButton->Location = System::Drawing::Point(36, 113);
			this->AddButton->Name = L"AddButton";
			this->AddButton->Size = System::Drawing::Size(81, 27);
			this->AddButton->TabIndex = 5;
			this->AddButton->Text = L"Add";
			this->AddButton->UseVisualStyleBackColor = true;
			this->AddButton->Click += gcnew System::EventHandler(this, &Erasmus::AddButton_Click);
			// 
			// EditButton
			// 
			this->EditButton->Location = System::Drawing::Point(36, 146);
			this->EditButton->Name = L"EditButton";
			this->EditButton->Size = System::Drawing::Size(81, 27);
			this->EditButton->TabIndex = 6;
			this->EditButton->Text = L"Edit";
			this->EditButton->UseVisualStyleBackColor = true;
			this->EditButton->Click += gcnew System::EventHandler(this, &Erasmus::EditButton_Click);
			// 
			// ShowComboBox
			// 
			this->ShowComboBox->FormattingEnabled = true;
			this->ShowComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"Elevi", L"Catalog", L"Universitati", L"Tari" });
			this->ShowComboBox->Location = System::Drawing::Point(6, 19);
			this->ShowComboBox->Name = L"ShowComboBox";
			this->ShowComboBox->Size = System::Drawing::Size(121, 21);
			this->ShowComboBox->TabIndex = 7;
			this->ShowComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Erasmus::ShowComboBox_SelectedIndexChanged);
			// 
			// ShowGroupBox
			// 
			this->ShowGroupBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->ShowGroupBox->Controls->Add(this->ShowComboBox);
			this->ShowGroupBox->Controls->Add(this->ShowButton);
			this->ShowGroupBox->Location = System::Drawing::Point(9, 419);
			this->ShowGroupBox->Name = L"ShowGroupBox";
			this->ShowGroupBox->Size = System::Drawing::Size(140, 112);
			this->ShowGroupBox->TabIndex = 8;
			this->ShowGroupBox->TabStop = false;
			// 
			// SearchGroupBox
			// 
			this->SearchGroupBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->SearchGroupBox->Controls->Add(this->SearchButton);
			this->SearchGroupBox->Controls->Add(this->SearchStudentTextBox);
			this->SearchGroupBox->Location = System::Drawing::Point(714, 27);
			this->SearchGroupBox->Name = L"SearchGroupBox";
			this->SearchGroupBox->Size = System::Drawing::Size(195, 35);
			this->SearchGroupBox->TabIndex = 9;
			this->SearchGroupBox->TabStop = false;
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) { this->FileMenu, this->OptionsMenu });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(921, 24);
			this->menuStrip1->TabIndex = 10;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// FileMenu
			// 
			this->FileMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->PrintOption });
			this->FileMenu->Name = L"FileMenu";
			this->FileMenu->Size = System::Drawing::Size(37, 20);
			this->FileMenu->Text = L"File";
			// 
			// PrintOption
			// 
			this->PrintOption->Name = L"PrintOption";
			this->PrintOption->Size = System::Drawing::Size(100, 23);
			this->PrintOption->Text = L"Print";
			// 
			// OptionsMenu
			// 
			this->OptionsMenu->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->ResetPasswordOption,
					this->ServerCredentialsOption, this->LoginFormOption
			});
			this->OptionsMenu->Name = L"OptionsMenu";
			this->OptionsMenu->Size = System::Drawing::Size(61, 20);
			this->OptionsMenu->Text = L"Options";
			// 
			// ResetPasswordOption
			// 
			this->ResetPasswordOption->Name = L"ResetPasswordOption";
			this->ResetPasswordOption->Size = System::Drawing::Size(100, 23);
			this->ResetPasswordOption->Text = L"Reset Password";
			this->ResetPasswordOption->Click += gcnew System::EventHandler(this, &Erasmus::ResetPasswordOption_Click);
			// 
			// ServerCredentialsOption
			// 
			this->ServerCredentialsOption->Name = L"ServerCredentialsOption";
			this->ServerCredentialsOption->Size = System::Drawing::Size(100, 23);
			this->ServerCredentialsOption->Text = L"Server Credentials";
			this->ServerCredentialsOption->Click += gcnew System::EventHandler(this, &Erasmus::ServerCredentialsOption_Click);
			// 
			// LoginFormOption
			// 
			this->LoginFormOption->Name = L"LoginFormOption";
			this->LoginFormOption->Size = System::Drawing::Size(100, 23);
			this->LoginFormOption->Text = L"Login Form";
			this->LoginFormOption->Click += gcnew System::EventHandler(this, &Erasmus::LoginFormOption_Click);
			// 
			// Erasmus
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(921, 534);
			this->Controls->Add(this->SearchGroupBox);
			this->Controls->Add(this->ShowGroupBox);
			this->Controls->Add(this->EditButton);
			this->Controls->Add(this->AddButton);
			this->Controls->Add(this->DeleteButton);
			this->Controls->Add(this->EleviDataGrid);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Erasmus";
			this->Text = L"Erasmus";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Erasmus::Erasmus_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &Erasmus::Erasmus_FormClosed);
			this->Load += gcnew System::EventHandler(this, &Erasmus::Erasmus_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EleviDataGrid))->EndInit();
			this->ShowGroupBox->ResumeLayout(false);
			this->SearchGroupBox->ResumeLayout(false);
			this->SearchGroupBox->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Erasmus_Load(System::Object^  sender, System::EventArgs^  e) {
		ShowButton->PerformClick();
	}
	private: System::Void ShowButton_Click(System::Object^  sender, System::EventArgs^  e) {
		
		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus."+option+";", conDataBase);
		MySqlDataReader^ myReader;

		ShowInDataGrid(cmdDataBase);

		EleviDataGrid->AutoSizeRowsMode = DataGridViewAutoSizeRowsMode::AllCells;
		EleviDataGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::AllCells;

		//ID,Nume,Prenume,Data_nastere,Tara_provenienta,Mail,Catalog,Facultatea
	}
	private: System::Void SearchButton_Click(System::Object^  sender, System::EventArgs^  e) {

		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select ID,Nume,Prenume,Data_nastere,Tara_provenienta,Mail,Catalog from erasmus.elevi  where Nume='"+SearchStudentTextBox->Text->ToUpper()+"';", conDataBase);
		MySqlDataReader^ myReader;

		ShowInDataGrid(cmdDataBase);
	}
private: System::Void SearchStudentTextBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Enter)
	{
		SearchButton->PerformClick();
	}
}
private: System::Void SearchStudentTextBox_Click(System::Object^  sender, System::EventArgs^  e) {
	SearchStudentTextBox->Clear();
}
private: System::Void SearchStudentTextBox_Leave(System::Object^  sender, System::EventArgs^  e) {
	SearchStudentTextBox->Text = "Search student here...";
}
private: System::Void DeleteButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (ShowComboBox->Text->Equals("Elevi")) deleteElev();
	if (ShowComboBox->Text->Equals("Catalog")) deleteCatalog();
	if (ShowComboBox->Text->Equals("Universitati")) deleteUniversitate();
	if (ShowComboBox->Text->Equals("Tari")) deleteTara();
}
private: System::Void AddButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if(ShowComboBox->Text->Equals("Elevi")) addElev();
	if (ShowComboBox->Text->Equals("Catalog")) addCatalog();
	if (ShowComboBox->Text->Equals("Universitati")) addUniversitate();
	if (ShowComboBox->Text->Equals("Tari")) addTara();
}
private: System::Void EditButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (ShowComboBox->Text->Equals("Elevi")) updateElev();
	if (ShowComboBox->Text->Equals("Catalog")) updateCatalog();
	if (ShowComboBox->Text->Equals("Universitati")) updateUni();
	if (ShowComboBox->Text->Equals("Tari")) updateTara();

}
private: System::Void ShowComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	option = ShowComboBox->Text->ToLower();
	ShowButton->Show();
	SearchButton->Show();
	SearchStudentTextBox->Show();

	if (!option->Equals("elevi"))
	{
		SearchButton->Hide();
		SearchStudentTextBox->Hide();
	}
}
private: System::Void Erasmus_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
	 Application::Exit();
}
private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void ResetPasswordOption_Click(System::Object^  sender, System::EventArgs^  e) {
	ResetPassword^ resetPassw = gcnew ResetPassword(userName);
	resetPassw->Show();
}
private: System::Void ServerCredentialsOption_Click(System::Object^  sender, System::EventArgs^  e) {
	ServerCredentials^ serverCred = gcnew ServerCredentials();
	serverCred->Show();
}
private: System::Void LoginFormOption_Click(System::Object^  sender, System::EventArgs^  e) {
	loginForm->Show();
	this->Hide();
}
private: System::Void Erasmus_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
}
};
}
