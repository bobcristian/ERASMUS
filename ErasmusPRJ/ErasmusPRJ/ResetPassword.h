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
	/// Summary for ResetPassword
	/// </summary>
	public ref class ResetPassword : public System::Windows::Forms::Form
	{
	public:
		ResetPassword(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		ResetPassword(String^ user)
		{
			InitializeComponent();
			userName = user;
			pictureBox1->Hide();
			pictureBox2->Hide();
			pictureBox3->Hide();
			pictureBox4->Hide();
			pictureBox5->Hide();
			pictureBox6->Hide();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ResetPassword()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  OldPasswordTextBox;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  NewPasswordTextBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  ConfirmPasswordTextBox;
	private: System::Windows::Forms::Button^  ResetButton;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::CheckBox^  ShowCheckBox;
	private: System::Windows::Forms::Button^  CancelButton;
	private:
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

		bool VerifyHash(String^ hashLogin, String^ hashFile)
		{
			return hashLogin->Equals(hashFile);
		}

	private:
		/// <summary>
		String^ userName;
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ResetPassword::typeid));
			this->OldPasswordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->NewPasswordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->ConfirmPasswordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ResetButton = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->CancelButton = (gcnew System::Windows::Forms::Button());
			this->ShowCheckBox = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			this->SuspendLayout();
			// 
			// OldPasswordTextBox
			// 
			this->OldPasswordTextBox->Location = System::Drawing::Point(135, 24);
			this->OldPasswordTextBox->Name = L"OldPasswordTextBox";
			this->OldPasswordTextBox->PasswordChar = '*';
			this->OldPasswordTextBox->Size = System::Drawing::Size(170, 20);
			this->OldPasswordTextBox->TabIndex = 0;
			this->OldPasswordTextBox->Leave += gcnew System::EventHandler(this, &ResetPassword::OldPasswordTextBox_Leave);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 27);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(72, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Old Password";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 69);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(78, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"New Password";
			// 
			// NewPasswordTextBox
			// 
			this->NewPasswordTextBox->Location = System::Drawing::Point(135, 66);
			this->NewPasswordTextBox->Name = L"NewPasswordTextBox";
			this->NewPasswordTextBox->PasswordChar = '*';
			this->NewPasswordTextBox->Size = System::Drawing::Size(170, 20);
			this->NewPasswordTextBox->TabIndex = 2;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 116);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(91, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Confirm Password";
			// 
			// ConfirmPasswordTextBox
			// 
			this->ConfirmPasswordTextBox->Location = System::Drawing::Point(135, 113);
			this->ConfirmPasswordTextBox->Name = L"ConfirmPasswordTextBox";
			this->ConfirmPasswordTextBox->PasswordChar = '*';
			this->ConfirmPasswordTextBox->Size = System::Drawing::Size(170, 20);
			this->ConfirmPasswordTextBox->TabIndex = 4;
			this->ConfirmPasswordTextBox->TextChanged += gcnew System::EventHandler(this, &ResetPassword::ConfirmPasswordTextBox_TextChanged);
			this->ConfirmPasswordTextBox->Leave += gcnew System::EventHandler(this, &ResetPassword::ConfirmPasswordTextBox_Leave);
			// 
			// ResetButton
			// 
			this->ResetButton->Location = System::Drawing::Point(322, 144);
			this->ResetButton->Name = L"ResetButton";
			this->ResetButton->Size = System::Drawing::Size(73, 28);
			this->ResetButton->TabIndex = 6;
			this->ResetButton->Text = L"Reset";
			this->ResetButton->UseVisualStyleBackColor = true;
			this->ResetButton->Click += gcnew System::EventHandler(this, &ResetPassword::ResetButton_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(322, 19);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(25, 25);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 7;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(370, 19);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(25, 25);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 8;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(370, 104);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(25, 25);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 10;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(322, 104);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(25, 25);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox4->TabIndex = 9;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(370, 61);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(25, 25);
			this->pictureBox5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox5->TabIndex = 12;
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox6
			// 
			this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.Image")));
			this->pictureBox6->Location = System::Drawing::Point(322, 61);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(25, 25);
			this->pictureBox6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox6->TabIndex = 11;
			this->pictureBox6->TabStop = false;
			// 
			// CancelButton
			// 
			this->CancelButton->Location = System::Drawing::Point(243, 144);
			this->CancelButton->Name = L"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(73, 28);
			this->CancelButton->TabIndex = 13;
			this->CancelButton->Text = L"Cancel";
			this->CancelButton->UseVisualStyleBackColor = true;
			this->CancelButton->Click += gcnew System::EventHandler(this, &ResetPassword::CancelButton_Click);
			// 
			// ShowCheckBox
			// 
			this->ShowCheckBox->AutoSize = true;
			this->ShowCheckBox->Location = System::Drawing::Point(135, 151);
			this->ShowCheckBox->Name = L"ShowCheckBox";
			this->ShowCheckBox->Size = System::Drawing::Size(107, 17);
			this->ShowCheckBox->TabIndex = 14;
			this->ShowCheckBox->Text = L"Show Passwords";
			this->ShowCheckBox->UseVisualStyleBackColor = true;
			this->ShowCheckBox->CheckedChanged += gcnew System::EventHandler(this, &ResetPassword::ShowCheckBox_CheckedChanged);
			// 
			// ResetPassword
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(404, 177);
			this->Controls->Add(this->ShowCheckBox);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->ResetButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->ConfirmPasswordTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->NewPasswordTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->OldPasswordTextBox);
			this->Name = L"ResetPassword";
			this->Text = L"ResetPassword";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void OldPasswordTextBox_Leave(System::Object^  sender, System::EventArgs^  e) {
		MD5^ md5hash = MD5::Create();
		String^ source = userName + "~" + OldPasswordTextBox->Text;
		String^ hash = GetMD5Hash(md5hash, source);

		if (VerifyHash(hash, ReadLogin()))
		{
			pictureBox1->Hide();
			pictureBox2->Show();
			pictureBox2->Enabled = true;
		}
		else
		{
			pictureBox1->Show();
			pictureBox2->Hide();
			pictureBox2->Enabled = false;
		}
	}
	private: System::Void ConfirmPasswordTextBox_Leave(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void CancelButton_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: System::Void ResetButton_Click(System::Object^  sender, System::EventArgs^  e) {
		MD5^ md5hash = MD5::Create();
		String^ source = userName + "~" + NewPasswordTextBox->Text;
		String^ hash = GetMD5Hash(md5hash, source);

		String^ fileName = "Login.txt";

		try
		{
			if ((!pictureBox2->Enabled) || (!pictureBox3->Enabled))
			{
				throw "Password is not correct!";
			}
			StreamWriter^ sw = gcnew StreamWriter(fileName);
			sw->Write(hash);
			sw->Close();
			MessageBox::Show("Password reset!");
			this->Close();
		}
		catch (String^ str)
		{
			MessageBox::Show(str);
		}
		catch (Exception^ ex)
		{
			MessageBox::Show(ex->Message);
		}
	}
private: System::Void ConfirmPasswordTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	if (NewPasswordTextBox->Text->Equals(ConfirmPasswordTextBox->Text))
	{
		pictureBox4->Hide();
		pictureBox3->Show();
		pictureBox3->Enabled = true;
	}
	else
	{
		pictureBox4->Show();
		pictureBox3->Hide();
		pictureBox3->Enabled = false;
	}
}
private: System::Void ShowCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (ShowCheckBox->CheckState == CheckState::Checked)
	{
		ConfirmPasswordTextBox->PasswordChar = '\0';
		OldPasswordTextBox->PasswordChar = '\0';
		NewPasswordTextBox->PasswordChar = '\0';
	}
	else
	{
		ConfirmPasswordTextBox->PasswordChar = '*';
		OldPasswordTextBox->PasswordChar = '*';
		NewPasswordTextBox->PasswordChar = '*';

	}
}
};
};
