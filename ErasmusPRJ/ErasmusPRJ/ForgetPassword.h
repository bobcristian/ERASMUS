#pragma once
#using<system.dll>

namespace ErasmusPRJ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::IO;
	using namespace System::Security::Cryptography;

	/// <summary>
	/// Summary for ForgetPassword
	/// </summary>
	public ref class ForgetPassword : public System::Windows::Forms::Form
	{
	public:
		ForgetPassword(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		ForgetPassword(System::Windows::Forms::Form^ form)
		{
			InitializeComponent();
			sendForm = form;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ForgetPassword()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  CodTextBox;
	protected:

	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  ParolaTextBox;
	private:
		String^ ReadLogin()
		{
			String^ fileName = "Login.txt";

			try
			{
				StreamReader^ reader = File::OpenText(fileName);

				String^ str = reader->ReadLine();
				reader->Close();
				return str;
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
			return "";
		}

		String^ ReadUser()
		{
			String^ fileName = "User.txt";

			try
			{
				StreamReader^ reader = File::OpenText(fileName);

				String^ str = reader->ReadLine();
				reader->Close();
				return str;
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
			return "";
		}

		String^ GetMD5Hash(MD5^ md5Hash, String^ input)
		{
			array<Byte>^ data = md5Hash->ComputeHash(Encoding::UTF8->GetBytes(input));
			StringBuilder^ sBuilder = gcnew StringBuilder();

			for (int i = 0; i < data->Length; i++)
			{
				sBuilder->Append(data[i].ToString("x2"));
			}

			return sBuilder->ToString();
		}

		void SavePassword(String^ hash)
		{
			String^ fileName = "Login.txt";

			StreamWriter^ sw = gcnew StreamWriter(fileName);
			sw->Write(hash);
			sw->Close();
			MessageBox::Show("Password saved!");
		}

	private: System::Windows::Forms::Button^  SaveButton;

	private:
		/// <summary>
		System::Windows::Forms::Form^ sendForm;
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->CodTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->ParolaTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// CodTextBox
			// 
			this->CodTextBox->Location = System::Drawing::Point(116, 42);
			this->CodTextBox->Name = L"CodTextBox";
			this->CodTextBox->Size = System::Drawing::Size(275, 20);
			this->CodTextBox->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(39, 45);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Cod";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(39, 113);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(64, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Parola noua";
			// 
			// ParolaTextBox
			// 
			this->ParolaTextBox->Location = System::Drawing::Point(116, 110);
			this->ParolaTextBox->Name = L"ParolaTextBox";
			this->ParolaTextBox->Size = System::Drawing::Size(275, 20);
			this->ParolaTextBox->TabIndex = 2;
			// 
			// SaveButton
			// 
			this->SaveButton->Location = System::Drawing::Point(311, 178);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(80, 28);
			this->SaveButton->TabIndex = 4;
			this->SaveButton->Text = L"Save";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &ForgetPassword::SaveButton_Click);
			// 
			// ForgetPassword
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(397, 213);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->ParolaTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->CodTextBox);
			this->Name = L"ForgetPassword";
			this->Text = L"ForgetPassword";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SaveButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (CodTextBox->Text->Equals(ReadLogin()))
		{
			MD5^ md5hash = MD5::Create();
			String^ source = ReadUser() + "~" + ParolaTextBox->Text;
			String^ hash = GetMD5Hash(md5hash, source);
			
			SavePassword(hash);

			sendForm->Close();
			this->Close();
		}
	}
};
}
