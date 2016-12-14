#pragma once
#include "AddStudent.h"
#include "UpdateStudent.h"

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
			ShowButton->Hide();
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
			
	private: String^ conString = L"datasource=localhost;port=3306;username=root;password=bobcrisaudir8;";
	private: System::Windows::Forms::TextBox^  SearchStudentTextBox;
	private: System::Windows::Forms::Button^  SearchButton;
			 /// <summary>
			 String^ option = "";
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EleviDataGrid))->BeginInit();
			this->SuspendLayout();
			// 
			// EleviDataGrid
			// 
			this->EleviDataGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->EleviDataGrid->Location = System::Drawing::Point(149, 68);
			this->EleviDataGrid->Name = L"EleviDataGrid";
			this->EleviDataGrid->Size = System::Drawing::Size(760, 454);
			this->EleviDataGrid->TabIndex = 0;
			// 
			// ShowButton
			// 
			this->ShowButton->Location = System::Drawing::Point(32, 488);
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
			this->SearchStudentTextBox->Location = System::Drawing::Point(761, 15);
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
			this->SearchButton->Location = System::Drawing::Point(724, 9);
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
			this->ShowComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Elevi", L"Catalog", L"Universitati" });
			this->ShowComboBox->Location = System::Drawing::Point(12, 461);
			this->ShowComboBox->Name = L"ShowComboBox";
			this->ShowComboBox->Size = System::Drawing::Size(121, 21);
			this->ShowComboBox->TabIndex = 7;
			this->ShowComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Erasmus::ShowComboBox_SelectedIndexChanged);
			// 
			// Erasmus
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(921, 534);
			this->Controls->Add(this->ShowComboBox);
			this->Controls->Add(this->EditButton);
			this->Controls->Add(this->AddButton);
			this->Controls->Add(this->DeleteButton);
			this->Controls->Add(this->SearchButton);
			this->Controls->Add(this->SearchStudentTextBox);
			this->Controls->Add(this->ShowButton);
			this->Controls->Add(this->EleviDataGrid);
			this->Name = L"Erasmus";
			this->Text = L"Erasmus";
			this->Load += gcnew System::EventHandler(this, &Erasmus::Erasmus_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->EleviDataGrid))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Erasmus_Load(System::Object^  sender, System::EventArgs^  e) {
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
		/*MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select ID,Nume,Prenume,Mail,Tara_provenienta,Catalog from erasmus.elevi where CNP='" + SearchStudentTextBox->Text + "';", conDataBase);
		MySqlDataReader^ myReader;

		ShowInDataGrid(cmdDataBase);*/
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
	MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
	if (EleviDataGrid->SelectedRows->Count > 0) {
		int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
		String^ toDelete = EleviDataGrid->Rows[rowIndex]->Cells["ID"]->Value->ToString();
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("delete from erasmus.elevi where ID='" + toDelete + "';", conDataBase);
		MySqlDataReader^ myReader;

		try {
			conDataBase->Open();
			myReader = cmdDataBase->ExecuteReader();
			ShowButton->PerformClick();
			while (myReader->Read())
			{

			}
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);
		}
	}
}
private: System::Void AddButton_Click(System::Object^  sender, System::EventArgs^  e) {
	AddStudent^ addStudent = gcnew AddStudent();
	addStudent->Show();
}
private: System::Void EditButton_Click(System::Object^  sender, System::EventArgs^  e) {
	MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
	if (EleviDataGrid->SelectedRows->Count > 0) {
		int rowIndex = EleviDataGrid->CurrentCell->RowIndex;
		String^ toEdit = EleviDataGrid->Rows[rowIndex]->Cells["ID"]->Value->ToString();
		UpdateStudent^ updateStud = gcnew UpdateStudent(toEdit,this);
		updateStud->Show();
		ShowButton->PerformClick();
	}
	
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
};
}
