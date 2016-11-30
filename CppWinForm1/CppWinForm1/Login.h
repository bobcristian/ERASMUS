#pragma once
#include "Erasmus.h"

namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Login
	/// </summary>
	public ref class Login : public System::Windows::Forms::Form
	{
	public:
		Login(void)
		{
			InitializeComponent();
			
			PswTextBox->PasswordChar = '*';
			PswTextBox->MaxLength = 10;
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
	private: System::Windows::Forms::Button^  LoginButton;
	private: System::Windows::Forms::TextBox^  UsrTextBox;
	private: System::Windows::Forms::TextBox^  PswTextBox;
	protected:


	private: System::Windows::Forms::Label^  UsrLabel;
	private: System::Windows::Forms::Label^  PswLabel;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
			 System::Windows::Forms::Form^ otherForm;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Login::typeid));
			this->LoginButton = (gcnew System::Windows::Forms::Button());
			this->UsrTextBox = (gcnew System::Windows::Forms::TextBox());
			this->PswTextBox = (gcnew System::Windows::Forms::TextBox());
			this->UsrLabel = (gcnew System::Windows::Forms::Label());
			this->PswLabel = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// LoginButton
			// 
			this->LoginButton->Location = System::Drawing::Point(481, 225);
			this->LoginButton->Name = L"LoginButton";
			this->LoginButton->Size = System::Drawing::Size(113, 42);
			this->LoginButton->TabIndex = 0;
			this->LoginButton->Text = L"Login";
			this->LoginButton->UseVisualStyleBackColor = true;
			this->LoginButton->Click += gcnew System::EventHandler(this, &Login::LoginButton_Click);
			// 
			// UsrTextBox
			// 
			this->UsrTextBox->Location = System::Drawing::Point(433, 117);
			this->UsrTextBox->Name = L"UsrTextBox";
			this->UsrTextBox->Size = System::Drawing::Size(205, 20);
			this->UsrTextBox->TabIndex = 1;
			// 
			// PswTextBox
			// 
			this->PswTextBox->Location = System::Drawing::Point(433, 167);
			this->PswTextBox->Name = L"PswTextBox";
			this->PswTextBox->Size = System::Drawing::Size(205, 20);
			this->PswTextBox->TabIndex = 2;
			// 
			// UsrLabel
			// 
			this->UsrLabel->AutoSize = true;
			this->UsrLabel->Location = System::Drawing::Point(370, 120);
			this->UsrLabel->Name = L"UsrLabel";
			this->UsrLabel->Size = System::Drawing::Size(55, 13);
			this->UsrLabel->TabIndex = 3;
			this->UsrLabel->Text = L"Username";
			this->UsrLabel->Click += gcnew System::EventHandler(this, &Login::label1_Click);
			// 
			// PswLabel
			// 
			this->PswLabel->AutoSize = true;
			this->PswLabel->Location = System::Drawing::Point(372, 170);
			this->PswLabel->Name = L"PswLabel";
			this->PswLabel->Size = System::Drawing::Size(53, 13);
			this->PswLabel->TabIndex = 4;
			this->PswLabel->Text = L"Password";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(57, 45);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(272, 253);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 5;
			this->pictureBox1->TabStop = false;
			// 
			// Login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(673, 450);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->PswLabel);
			this->Controls->Add(this->UsrLabel);
			this->Controls->Add(this->PswTextBox);
			this->Controls->Add(this->UsrTextBox);
			this->Controls->Add(this->LoginButton);
			this->Name = L"Login";
			this->Text = L"Login";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void LoginButton_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->UsrTextBox->Text == "Cristi" && this->PswTextBox->Text == "Bob")
		{
			Erasmus^ ers = gcnew Erasmus(this);

			//MessageBox::Show("Correct!");
			ers->Show();
			this->Hide();
		}
		else
		{
			MessageBox::Show("Incorect");
		}
	}
};
}
