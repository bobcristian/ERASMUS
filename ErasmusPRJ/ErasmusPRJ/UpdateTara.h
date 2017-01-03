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
	/// Summary for UpdateTara
	/// </summary>
	public ref class UpdateTara : public System::Windows::Forms::Form
	{
	public:
		UpdateTara(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		UpdateTara(String^ edit)
		{
			InitializeComponent();
			toEdit = edit;
			populate();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UpdateTara()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  UpdateButton;
	protected:

	protected:
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  IndicativTextBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  TaraTextBox;
	private:
		void populate()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.tari where ID='" + toEdit + "';", conDataBase);
			MySqlDataReader^ myReader;

			try
			{
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();
				myReader->Read();

				TaraTextBox->Text = myReader->GetString("Nume_tara");
				IndicativTextBox->Text = myReader->GetString("Cod_tara");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

	private:
		/// <summary>
		String^ conString = L"datasource=localhost;port=3306;username=root;password=bobcrisaudir8;";
		String^ toEdit;
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
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->IndicativTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->TaraTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// UpdateButton
			// 
			this->UpdateButton->Location = System::Drawing::Point(208, 228);
			this->UpdateButton->Name = L"UpdateButton";
			this->UpdateButton->Size = System::Drawing::Size(85, 37);
			this->UpdateButton->TabIndex = 9;
			this->UpdateButton->Text = L"Update";
			this->UpdateButton->UseVisualStyleBackColor = true;
			this->UpdateButton->Click += gcnew System::EventHandler(this, &UpdateTara::UpdateButton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(23, 110);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(47, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Indicativ";
			// 
			// IndicativTextBox
			// 
			this->IndicativTextBox->Location = System::Drawing::Point(85, 107);
			this->IndicativTextBox->Name = L"IndicativTextBox";
			this->IndicativTextBox->Size = System::Drawing::Size(176, 20);
			this->IndicativTextBox->TabIndex = 7;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(23, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(29, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Tara";
			// 
			// TaraTextBox
			// 
			this->TaraTextBox->Location = System::Drawing::Point(85, 27);
			this->TaraTextBox->Name = L"TaraTextBox";
			this->TaraTextBox->Size = System::Drawing::Size(176, 20);
			this->TaraTextBox->TabIndex = 5;
			// 
			// UpdateTara
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(305, 277);
			this->Controls->Add(this->UpdateButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->IndicativTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TaraTextBox);
			this->Name = L"UpdateTara";
			this->Text = L"UpdateTara";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void UpdateButton_Click(System::Object^  sender, System::EventArgs^  e) {
		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("update erasmus.tari SET Cod_tara='" + IndicativTextBox->Text->ToUpper() + "',Nume_tara='" + TaraTextBox->Text + "' where ID='" + toEdit + "';", conDataBase);
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
