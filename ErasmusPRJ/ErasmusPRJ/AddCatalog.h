#pragma once

namespace ErasmusPRJ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	/// <summary>
	/// Summary for AddCatalog
	/// </summary>
	public ref class AddCatalog : public System::Windows::Forms::Form
	{
	public:
		AddCatalog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AddCatalog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  NumeTextBox;
	protected:

	protected:
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  ECTSTextBox;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  CodTextBox;
	private: System::Windows::Forms::Button^  AddButton;


	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
			String^ conString = L"datasource=localhost;port=3306;username=root;password=bobcrisaudir8;";
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->NumeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->ECTSTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->CodTextBox = (gcnew System::Windows::Forms::TextBox());
			this->AddButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// NumeTextBox
			// 
			this->NumeTextBox->Location = System::Drawing::Point(70, 25);
			this->NumeTextBox->Name = L"NumeTextBox";
			this->NumeTextBox->Size = System::Drawing::Size(222, 20);
			this->NumeTextBox->TabIndex = 0;
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(61, 4);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 28);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Nume";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 118);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"ECTS";
			// 
			// ECTSTextBox
			// 
			this->ECTSTextBox->Location = System::Drawing::Point(70, 115);
			this->ECTSTextBox->Name = L"ECTSTextBox";
			this->ECTSTextBox->Size = System::Drawing::Size(38, 20);
			this->ECTSTextBox->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 73);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(26, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Cod";
			// 
			// CodTextBox
			// 
			this->CodTextBox->Location = System::Drawing::Point(70, 70);
			this->CodTextBox->Name = L"CodTextBox";
			this->CodTextBox->Size = System::Drawing::Size(222, 20);
			this->CodTextBox->TabIndex = 5;
			// 
			// AddButton
			// 
			this->AddButton->Location = System::Drawing::Point(187, 217);
			this->AddButton->Name = L"AddButton";
			this->AddButton->Size = System::Drawing::Size(105, 37);
			this->AddButton->TabIndex = 7;
			this->AddButton->Text = L"Add";
			this->AddButton->UseVisualStyleBackColor = true;
			this->AddButton->Click += gcnew System::EventHandler(this, &AddCatalog::AddButton_Click);
			// 
			// AddCatalog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(296, 266);
			this->Controls->Add(this->AddButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->CodTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->ECTSTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->NumeTextBox);
			this->Name = L"AddCatalog";
			this->Text = L"AddCatalog";
			this->Load += gcnew System::EventHandler(this, &AddCatalog::AddCatalog_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AddCatalog_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void AddButton_Click(System::Object^  sender, System::EventArgs^  e) {
		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("insert into erasmus.catalog (Nume_curs,Cod_curs,ECTS) values('" + NumeTextBox->Text + "','" + CodTextBox->Text->ToUpper() + "','" + ECTSTextBox->Text + "');", conDataBase);
		MySqlDataReader^ myReader;

		if (MessageBox::Show("Sunteti sigur ca datele sunt corecte?",
			"Add Student", MessageBoxButtons::YesNo,
			MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
			try
			{
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();
				myReader->Read();
				this->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}
	}
};
}
