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
	/// Summary for AddUniversitate
	/// </summary>
	public ref class AddUniversitate : public System::Windows::Forms::Form
	{
	public:
		AddUniversitate(void)
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
		~AddUniversitate()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  NumeTextBox;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  CodTextBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  ContactTextBox;
	private: System::Windows::Forms::Button^  AddButton;
	private:
		String^ persoanaContact()
		{
			String^ toParse = ContactTextBox->Text;
			array<String^>^ contact;
			String^ toReturn="";

			contact = toParse->Split(' ');
			contact[contact->Length - 1]=contact[contact->Length - 1]->ToUpper();
			for (int i = 0; i < contact->Length; i++)
			{
				toReturn = toReturn + contact[i] + " ";
			}

			return toReturn;
		}

	private:
		/// <summary>
		String^ conString = L"datasource=localhost;port=3306;username=root;password=bobcrisaudir8;";
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->NumeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->CodTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->ContactTextBox = (gcnew System::Windows::Forms::TextBox());
			this->AddButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// NumeTextBox
			// 
			this->NumeTextBox->Location = System::Drawing::Point(89, 46);
			this->NumeTextBox->Name = L"NumeTextBox";
			this->NumeTextBox->Size = System::Drawing::Size(293, 20);
			this->NumeTextBox->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(29, 49);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Nume";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(29, 96);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(26, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Cod";
			// 
			// CodTextBox
			// 
			this->CodTextBox->Location = System::Drawing::Point(89, 96);
			this->CodTextBox->Name = L"CodTextBox";
			this->CodTextBox->Size = System::Drawing::Size(293, 20);
			this->CodTextBox->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(29, 153);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Persoana contact";
			// 
			// ContactTextBox
			// 
			this->ContactTextBox->Location = System::Drawing::Point(126, 150);
			this->ContactTextBox->Name = L"ContactTextBox";
			this->ContactTextBox->Size = System::Drawing::Size(256, 20);
			this->ContactTextBox->TabIndex = 4;
			// 
			// AddButton
			// 
			this->AddButton->Location = System::Drawing::Point(316, 300);
			this->AddButton->Name = L"AddButton";
			this->AddButton->Size = System::Drawing::Size(82, 36);
			this->AddButton->TabIndex = 6;
			this->AddButton->Text = L"Add";
			this->AddButton->UseVisualStyleBackColor = true;
			this->AddButton->Click += gcnew System::EventHandler(this, &AddUniversitate::AddButton_Click);
			// 
			// AddUniversitate
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(410, 348);
			this->Controls->Add(this->AddButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->ContactTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->CodTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->NumeTextBox);
			this->Name = L"AddUniversitate";
			this->Text = L"AddUniversitate";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AddButton_Click(System::Object^  sender, System::EventArgs^  e) {
		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("insert into erasmus.universitati (Universitatea,Cod_acord,Pers_contact) values('" + NumeTextBox->Text + "','" + CodTextBox->Text->ToUpper() + "','" + persoanaContact() +"');", conDataBase);
		MySqlDataReader^ myReader;

		try
		{
			conDataBase->Open();
			myReader = cmdDataBase->ExecuteReader();
			myReader->Read();
			MessageBox::Show("Datele au fost salvate cu success!");
			this->Close();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);
		}
	}
};
}
