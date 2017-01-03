#pragma once
#using<system.dll>
#include "ForgetPassword.h"

namespace ErasmusPRJ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Text;
	using namespace System::IO;

	using namespace System::Web;
	using namespace System::Net::Mail;

	/// <summary>
	/// Summary for SendEmail
	/// </summary>
	public ref class SendEmail : public System::Windows::Forms::Form
	{
	public:
		SendEmail(void)
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
		~SendEmail()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  UserTextBox;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  MailTextBox;
	private: System::Windows::Forms::Button^  SendButton;
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

	private:
		/// <summary>
		String^ from = "proiect_erasmus2017@yahoo.com";
		String^ to;
		String^ pass = "erasmusteam2017";
		String^ subject = "Recuperare parola";
		String^ body;
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->UserTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->MailTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SendButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// UserTextBox
			// 
			this->UserTextBox->Location = System::Drawing::Point(102, 36);
			this->UserTextBox->Name = L"UserTextBox";
			this->UserTextBox->Size = System::Drawing::Size(144, 20);
			this->UserTextBox->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(29, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"User";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 99);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"E-mail";
			// 
			// MailTextBox
			// 
			this->MailTextBox->Location = System::Drawing::Point(102, 96);
			this->MailTextBox->Name = L"MailTextBox";
			this->MailTextBox->Size = System::Drawing::Size(144, 20);
			this->MailTextBox->TabIndex = 2;
			// 
			// SendButton
			// 
			this->SendButton->Location = System::Drawing::Point(208, 143);
			this->SendButton->Name = L"SendButton";
			this->SendButton->Size = System::Drawing::Size(75, 31);
			this->SendButton->TabIndex = 4;
			this->SendButton->Text = L"Send";
			this->SendButton->UseVisualStyleBackColor = true;
			this->SendButton->Click += gcnew System::EventHandler(this, &SendEmail::SendButton_Click);
			// 
			// SendEmail
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(286, 176);
			this->Controls->Add(this->SendButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->MailTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->UserTextBox);
			this->Name = L"SendEmail";
			this->Text = L"SendEmail";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SendButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (UserTextBox->Text->Equals(ReadUser()))
		{
			body = "Introduceti codul urmator in aplicatie pentru a va recupera parola: " + ReadLogin();
			String^ smtp = "smtp.mail.yahoo.com";
			to = MailTextBox->Text;

			try {
				MailMessage^ mail = gcnew MailMessage(from, to, subject, body);

				SmtpClient^ client = gcnew SmtpClient(smtp);
				client->Port = 587;
				client->Credentials = gcnew System::Net::NetworkCredential(from, pass);
				client->EnableSsl = true;
				client->Send(mail);
				MessageBox::Show("Mail Sent!", "Success!", MessageBoxButtons::OK);
				
				ForgetPassword^ forget = gcnew ForgetPassword(this);
				forget->Show();
				this->Hide();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}
		else
		{
			MessageBox::Show("User incorect!");
		}
	}
};
}
