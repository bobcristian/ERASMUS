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
	/// Summary for UpdateUniversitate
	/// </summary>
	public ref class UpdateUniversitate : public System::Windows::Forms::Form
	{
	public:
		UpdateUniversitate(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		UpdateUniversitate(String^ edit)
		{
			InitializeComponent();
			toEdit = edit;
			populate();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UpdateUniversitate()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  UpdateButton;
	protected:
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  ContactTextBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  CodTextBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  NumeTextBox;
	private:
		void populate()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.universitati where ID='"+toEdit+"';", conDataBase);
			MySqlDataReader^ myReader;

			try
			{
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();
				myReader->Read();
				NumeTextBox->Text = myReader->GetString("Universitatea");
				CodTextBox->Text = myReader->GetString("Cod_acord");
				ContactTextBox->Text = myReader->GetString("Pers_contact");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

		String^ persoanaContact()
		{
			String^ toParse = ContactTextBox->Text;
			array<String^>^ contact;
			String^ toReturn = "";

			contact = toParse->Split(' ');
			contact[contact->Length - 1] = contact[contact->Length - 1]->ToUpper();
			for (int i = 0; i < contact->Length; i++)
			{
				toReturn = toReturn + contact[i] + " ";
			}

			return toReturn;
		}

	private:
		/// <summary>
		String^ toEdit;
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
			this->UpdateButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->ContactTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->CodTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->NumeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// UpdateButton
			// 
			this->UpdateButton->Location = System::Drawing::Point(305, 294);
			this->UpdateButton->Name = L"UpdateButton";
			this->UpdateButton->Size = System::Drawing::Size(82, 36);
			this->UpdateButton->TabIndex = 13;
			this->UpdateButton->Text = L"Update";
			this->UpdateButton->UseVisualStyleBackColor = true;
			this->UpdateButton->Click += gcnew System::EventHandler(this, &UpdateUniversitate::UpdateButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(18, 147);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 13);
			this->label3->TabIndex = 12;
			this->label3->Text = L"Persoana contact";
			// 
			// ContactTextBox
			// 
			this->ContactTextBox->Location = System::Drawing::Point(115, 144);
			this->ContactTextBox->Name = L"ContactTextBox";
			this->ContactTextBox->Size = System::Drawing::Size(256, 20);
			this->ContactTextBox->TabIndex = 11;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(18, 90);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(26, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Cod";
			// 
			// CodTextBox
			// 
			this->CodTextBox->Location = System::Drawing::Point(78, 90);
			this->CodTextBox->Name = L"CodTextBox";
			this->CodTextBox->Size = System::Drawing::Size(293, 20);
			this->CodTextBox->TabIndex = 9;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(18, 43);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Nume";
			// 
			// NumeTextBox
			// 
			this->NumeTextBox->Location = System::Drawing::Point(78, 40);
			this->NumeTextBox->Name = L"NumeTextBox";
			this->NumeTextBox->Size = System::Drawing::Size(293, 20);
			this->NumeTextBox->TabIndex = 7;
			// 
			// UpdateUniversitate
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(393, 337);
			this->Controls->Add(this->UpdateButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->ContactTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->CodTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->NumeTextBox);
			this->Name = L"UpdateUniversitate";
			this->Text = L"UpdateUniversitate";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void UpdateButton_Click(System::Object^  sender, System::EventArgs^  e) {
		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("update erasmus.universitati SET Universitatea='" + NumeTextBox->Text + "',Cod_acord='" + CodTextBox->Text->ToUpper() + "',Pers_contact='" + persoanaContact() + "' where ID='" + toEdit + "';", conDataBase);
		MySqlDataReader^ myReader;

		try
		{
			conDataBase->Open();
			myReader = cmdDataBase->ExecuteReader();
			myReader->Read();
			MessageBox::Show("Datele au fost updatate cu succes!");
			this->Close();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);
		}
	}
};
}
