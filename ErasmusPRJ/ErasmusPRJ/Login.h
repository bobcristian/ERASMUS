#pragma once
#using<system.dll>
#include "ServerCredentials.h"
#include "Erasmus.h"
#include "SendEmail.h"

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
	/// Summary for Login
	/// </summary>
	public ref class Login : public System::Windows::Forms::Form
	{
	public:
		Login(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Login()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::TextBox^  UserTextBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  PasswordTextBox;
	private: System::Windows::Forms::Button^  LoginButton;
	private: System::Windows::Forms::LinkLabel^  ForgetLink;
	private: System::Windows::Forms::LinkLabel^  ServerConnectionLink;
	private: System::Windows::Forms::TextBox^  HashTextBox;
	private: System::Windows::Forms::Button^  GuestButton;
	private: System::Windows::Forms::CheckBox^  ShowCheckBox;
	private: System::Windows::Forms::Button^  HashButton;
	protected:
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

				String^ str=reader->ReadLine();
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



		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Login::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->UserTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->PasswordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->LoginButton = (gcnew System::Windows::Forms::Button());
			this->ForgetLink = (gcnew System::Windows::Forms::LinkLabel());
			this->ServerConnectionLink = (gcnew System::Windows::Forms::LinkLabel());
			this->HashTextBox = (gcnew System::Windows::Forms::TextBox());
			this->HashButton = (gcnew System::Windows::Forms::Button());
			this->GuestButton = (gcnew System::Windows::Forms::Button());
			this->ShowCheckBox = (gcnew System::Windows::Forms::CheckBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(12, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(353, 359);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Login::pictureBox1_Click);
			// 
			// UserTextBox
			// 
			this->UserTextBox->Location = System::Drawing::Point(456, 67);
			this->UserTextBox->Name = L"UserTextBox";
			this->UserTextBox->Size = System::Drawing::Size(140, 20);
			this->UserTextBox->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(401, 70);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(29, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"User";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(401, 133);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Password";
			// 
			// PasswordTextBox
			// 
			this->PasswordTextBox->Location = System::Drawing::Point(456, 130);
			this->PasswordTextBox->Name = L"PasswordTextBox";
			this->PasswordTextBox->PasswordChar = '*';
			this->PasswordTextBox->Size = System::Drawing::Size(140, 20);
			this->PasswordTextBox->TabIndex = 3;
			this->PasswordTextBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Login::PasswordTextBox_KeyDown);
			// 
			// LoginButton
			// 
			this->LoginButton->Location = System::Drawing::Point(404, 234);
			this->LoginButton->Name = L"LoginButton";
			this->LoginButton->Size = System::Drawing::Size(192, 30);
			this->LoginButton->TabIndex = 5;
			this->LoginButton->Text = L"Login";
			this->LoginButton->UseVisualStyleBackColor = true;
			this->LoginButton->Click += gcnew System::EventHandler(this, &Login::LoginButton_Click);
			// 
			// ForgetLink
			// 
			this->ForgetLink->AutoSize = true;
			this->ForgetLink->Location = System::Drawing::Point(401, 334);
			this->ForgetLink->Name = L"ForgetLink";
			this->ForgetLink->Size = System::Drawing::Size(85, 13);
			this->ForgetLink->TabIndex = 6;
			this->ForgetLink->TabStop = true;
			this->ForgetLink->Text = L"Forget password";
			this->ForgetLink->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Login::ForgetLink_LinkClicked);
			// 
			// ServerConnectionLink
			// 
			this->ServerConnectionLink->AutoSize = true;
			this->ServerConnectionLink->Location = System::Drawing::Point(401, 358);
			this->ServerConnectionLink->Name = L"ServerConnectionLink";
			this->ServerConnectionLink->Size = System::Drawing::Size(148, 13);
			this->ServerConnectionLink->TabIndex = 7;
			this->ServerConnectionLink->TabStop = true;
			this->ServerConnectionLink->Text = L"Server connection credentials";
			this->ServerConnectionLink->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &Login::ServerConnectionLink_LinkClicked);
			// 
			// HashTextBox
			// 
			this->HashTextBox->Location = System::Drawing::Point(456, 404);
			this->HashTextBox->Name = L"HashTextBox";
			this->HashTextBox->Size = System::Drawing::Size(157, 20);
			this->HashTextBox->TabIndex = 8;
			// 
			// HashButton
			// 
			this->HashButton->Location = System::Drawing::Point(359, 398);
			this->HashButton->Name = L"HashButton";
			this->HashButton->Size = System::Drawing::Size(91, 30);
			this->HashButton->TabIndex = 9;
			this->HashButton->Text = L"Hash";
			this->HashButton->UseVisualStyleBackColor = true;
			this->HashButton->Click += gcnew System::EventHandler(this, &Login::HashButton_Click);
			// 
			// GuestButton
			// 
			this->GuestButton->Location = System::Drawing::Point(404, 281);
			this->GuestButton->Name = L"GuestButton";
			this->GuestButton->Size = System::Drawing::Size(192, 30);
			this->GuestButton->TabIndex = 10;
			this->GuestButton->Text = L"Guest";
			this->GuestButton->UseVisualStyleBackColor = true;
			this->GuestButton->Click += gcnew System::EventHandler(this, &Login::GuestButton_Click);
			// 
			// ShowCheckBox
			// 
			this->ShowCheckBox->AutoSize = true;
			this->ShowCheckBox->Location = System::Drawing::Point(494, 170);
			this->ShowCheckBox->Name = L"ShowCheckBox";
			this->ShowCheckBox->Size = System::Drawing::Size(102, 17);
			this->ShowCheckBox->TabIndex = 11;
			this->ShowCheckBox->Text = L"Show Password";
			this->ShowCheckBox->UseVisualStyleBackColor = true;
			this->ShowCheckBox->CheckedChanged += gcnew System::EventHandler(this, &Login::ShowCheckBox_CheckedChanged);
			// 
			// Login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(625, 451);
			this->Controls->Add(this->ShowCheckBox);
			this->Controls->Add(this->GuestButton);
			this->Controls->Add(this->HashButton);
			this->Controls->Add(this->HashTextBox);
			this->Controls->Add(this->ServerConnectionLink);
			this->Controls->Add(this->ForgetLink);
			this->Controls->Add(this->LoginButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->PasswordTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->UserTextBox);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Login";
			this->Text = L"Login";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void ServerConnectionLink_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
		ServerCredentials^ serverCredentials = gcnew ServerCredentials();
		serverCredentials->Show();
	}
private: System::Void HashButton_Click(System::Object^  sender, System::EventArgs^  e) {
	MD5^ md5hash = MD5::Create();
	String^ source = UserTextBox->Text + "~" + PasswordTextBox->Text;
	String^ hash = GetMD5Hash(md5hash, source);
	HashTextBox->Text = hash;
}
private: System::Void DecryptButton_Click(System::Object^  sender, System::EventArgs^  e) {
	
}
private: System::Void LoginButton_Click(System::Object^  sender, System::EventArgs^  e) {
	MD5^ md5hash = MD5::Create();
	String^ source = UserTextBox->Text + "~" + PasswordTextBox->Text;
	String^ hash = GetMD5Hash(md5hash, source);
	
	if (VerifyHash(hash, ReadLogin()))
	{
		Erasmus^ ers = gcnew Erasmus(this,UserTextBox->Text);
		ers->Show();
		this->Hide();
	}
	else
	{
		MessageBox::Show("Authentification fail!");
	}

}
private: System::Void GuestButton_Click(System::Object^  sender, System::EventArgs^  e) {
	Erasmus^ ers = gcnew Erasmus(this,"Guest");
	ers->Show();
	this->Hide();
}
private: System::Void PasswordTextBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
	if (e->KeyCode == Keys::Enter)
	{
		LoginButton->PerformClick();
	}
}
private: System::Void ShowCheckBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (ShowCheckBox->CheckState==CheckState::Checked) PasswordTextBox->PasswordChar='\0';
	else PasswordTextBox->PasswordChar = '*';
}
private: System::Void ForgetLink_LinkClicked(System::Object^  sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^  e) {
	SendEmail^ sendMail = gcnew SendEmail();
	sendMail->Show();
}
};
}
