#pragma once

namespace CppWinForm1 {

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
		}

		Erasmus(System::Windows::Forms::Form^ login)
		{
			otherForm = login;
			InitializeComponent();
		}

	private: System::Windows::Forms::Form^ otherForm;

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
	private: System::Windows::Forms::Button^  AddButton;
	protected:
	private: System::Windows::Forms::Button^  DeleteButton;
	private: System::Windows::Forms::Button^  EditButton;
	private: System::Windows::Forms::TextBox^  SearchBox;
	private: System::Windows::Forms::Button^  SearchButton;
	private: System::Windows::Forms::TextBox^  ViewDataBase;

	private: System::Windows::Forms::Button^  ViewButton;



	private:
		/// <summary>
		/// Required designer variable.
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
			this->AddButton = (gcnew System::Windows::Forms::Button());
			this->DeleteButton = (gcnew System::Windows::Forms::Button());
			this->EditButton = (gcnew System::Windows::Forms::Button());
			this->SearchBox = (gcnew System::Windows::Forms::TextBox());
			this->SearchButton = (gcnew System::Windows::Forms::Button());
			this->ViewDataBase = (gcnew System::Windows::Forms::TextBox());
			this->ViewButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// AddButton
			// 
			this->AddButton->Location = System::Drawing::Point(25, 24);
			this->AddButton->Name = L"AddButton";
			this->AddButton->Size = System::Drawing::Size(103, 30);
			this->AddButton->TabIndex = 0;
			this->AddButton->Text = L"Add";
			this->AddButton->UseVisualStyleBackColor = true;
			// 
			// DeleteButton
			// 
			this->DeleteButton->Location = System::Drawing::Point(25, 60);
			this->DeleteButton->Name = L"DeleteButton";
			this->DeleteButton->Size = System::Drawing::Size(103, 30);
			this->DeleteButton->TabIndex = 1;
			this->DeleteButton->Text = L"Delete";
			this->DeleteButton->UseVisualStyleBackColor = true;
			// 
			// EditButton
			// 
			this->EditButton->Location = System::Drawing::Point(25, 96);
			this->EditButton->Name = L"EditButton";
			this->EditButton->Size = System::Drawing::Size(103, 30);
			this->EditButton->TabIndex = 2;
			this->EditButton->Text = L"Edit";
			this->EditButton->UseVisualStyleBackColor = true;
			// 
			// SearchBox
			// 
			this->SearchBox->ForeColor = System::Drawing::SystemColors::ScrollBar;
			this->SearchBox->Location = System::Drawing::Point(579, 22);
			this->SearchBox->Name = L"SearchBox";
			this->SearchBox->Size = System::Drawing::Size(228, 20);
			this->SearchBox->TabIndex = 3;
			this->SearchBox->Text = L"Search a student here";
			// 
			// SearchButton
			// 
			this->SearchButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"SearchButton.Image")));
			this->SearchButton->Location = System::Drawing::Point(539, 16);
			this->SearchButton->Name = L"SearchButton";
			this->SearchButton->Size = System::Drawing::Size(34, 30);
			this->SearchButton->TabIndex = 4;
			this->SearchButton->UseVisualStyleBackColor = true;
			this->SearchButton->Click += gcnew System::EventHandler(this, &Erasmus::SearchButton_Click);
			// 
			// ViewDataBase
			// 
			this->ViewDataBase->Location = System::Drawing::Point(183, 139);
			this->ViewDataBase->Multiline = true;
			this->ViewDataBase->Name = L"ViewDataBase";
			this->ViewDataBase->Size = System::Drawing::Size(614, 273);
			this->ViewDataBase->TabIndex = 5;
			// 
			// ViewButton
			// 
			this->ViewButton->Location = System::Drawing::Point(152, 24);
			this->ViewButton->Name = L"ViewButton";
			this->ViewButton->Size = System::Drawing::Size(103, 30);
			this->ViewButton->TabIndex = 6;
			this->ViewButton->Text = L"View";
			this->ViewButton->UseVisualStyleBackColor = true;
			this->ViewButton->Click += gcnew System::EventHandler(this, &Erasmus::ViewButton_Click);
			// 
			// Erasmus
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(843, 496);
			this->Controls->Add(this->ViewButton);
			this->Controls->Add(this->ViewDataBase);
			this->Controls->Add(this->SearchButton);
			this->Controls->Add(this->SearchBox);
			this->Controls->Add(this->EditButton);
			this->Controls->Add(this->DeleteButton);
			this->Controls->Add(this->AddButton);
			this->Name = L"Erasmus";
			this->Text = L"Erasmus";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Erasmus::Erasmus_FormClosing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void ViewButton_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ constring = L"datasource=localhost; port=3306;username=root;password=bobcrisaudir8";
		MySqlConnection^ conDataBase = gcnew MySqlConnection(constring);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from sakila.actor;", conDataBase);
		MySqlDataReader^ myReader;
		try {
			conDataBase->Open();
			myReader = cmdDataBase->ExecuteReader();

			while (myReader->Read())
			{
				ViewDataBase->Text += (myReader->GetInt32(0));
				ViewDataBase->Text += "\n";
			}
		}
		catch (Exception^ex) {
			MessageBox::Show(ex->Message);
		}
	
	}
	private: System::Void SearchButton_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void Erasmus_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		Application::Exit();
	}
};
}
