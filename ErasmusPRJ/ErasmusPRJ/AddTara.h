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
	/// Summary for AddTara
	/// </summary>
	public ref class AddTara : public System::Windows::Forms::Form
	{
	public:
		AddTara(void)
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
		~AddTara()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  TaraTextBox;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  IndicativTextBox;
	private: System::Windows::Forms::Button^  AddButton;

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
			this->TaraTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->IndicativTextBox = (gcnew System::Windows::Forms::TextBox());
			this->AddButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// TaraTextBox
			// 
			this->TaraTextBox->Location = System::Drawing::Point(86, 41);
			this->TaraTextBox->Name = L"TaraTextBox";
			this->TaraTextBox->Size = System::Drawing::Size(151, 20);
			this->TaraTextBox->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(24, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(29, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Tara";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(24, 124);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(47, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Indicativ";
			// 
			// IndicativTextBox
			// 
			this->IndicativTextBox->Location = System::Drawing::Point(86, 121);
			this->IndicativTextBox->Name = L"IndicativTextBox";
			this->IndicativTextBox->Size = System::Drawing::Size(151, 20);
			this->IndicativTextBox->TabIndex = 2;
			// 
			// AddButton
			// 
			this->AddButton->Location = System::Drawing::Point(189, 219);
			this->AddButton->Name = L"AddButton";
			this->AddButton->Size = System::Drawing::Size(73, 31);
			this->AddButton->TabIndex = 4;
			this->AddButton->Text = L"Add";
			this->AddButton->UseVisualStyleBackColor = true;
			this->AddButton->Click += gcnew System::EventHandler(this, &AddTara::AddButton_Click);
			// 
			// AddTara
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(274, 262);
			this->Controls->Add(this->AddButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->IndicativTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TaraTextBox);
			this->Name = L"AddTara";
			this->Text = L"AddTara";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AddButton_Click(System::Object^  sender, System::EventArgs^  e) {
		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("insert into erasmus.tari (Cod_tara,Nume_tara) values('" + IndicativTextBox->Text->ToUpper() + "','" + TaraTextBox->Text + "');", conDataBase);
		MySqlDataReader^ myReader;

		try
		{
			conDataBase->Open();
			myReader = cmdDataBase->ExecuteReader();
			myReader->Read();
			MessageBox::Show("Datele au fost salvate cu succes!");
			this->Close();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);
		}
	}
};
}
