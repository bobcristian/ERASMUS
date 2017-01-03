#pragma once

namespace ErasmusPRJ {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace MySql::Data::MySqlClient;

	/// <summary>
	/// Summary for ServerCredentials
	/// </summary>
	public ref class ServerCredentials : public System::Windows::Forms::Form
	{
	public:
		ServerCredentials(void)
		{
			InitializeComponent();
			SaveButton->Enabled=false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ServerCredentials()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  PortTextBox;
	protected:

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  UserTextBox;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  PasswordTextBox;

	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  HostTextBox;
	private: System::Windows::Forms::Button^  TestButton;
	private: System::Windows::Forms::Button^  SaveButton;


	private:
		/// <summary>
		String^ conString;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
			 /// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ServerCredentials::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->PortTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->UserTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->PasswordTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->HostTextBox = (gcnew System::Windows::Forms::TextBox());
			this->TestButton = (gcnew System::Windows::Forms::Button());
			this->SaveButton = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(340, 72);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Port";
			// 
			// PortTextBox
			// 
			this->PortTextBox->Location = System::Drawing::Point(395, 69);
			this->PortTextBox->Name = L"PortTextBox";
			this->PortTextBox->Size = System::Drawing::Size(140, 20);
			this->PortTextBox->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(340, 98);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(29, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"User";
			// 
			// UserTextBox
			// 
			this->UserTextBox->Location = System::Drawing::Point(395, 95);
			this->UserTextBox->Name = L"UserTextBox";
			this->UserTextBox->Size = System::Drawing::Size(140, 20);
			this->UserTextBox->TabIndex = 5;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(340, 124);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(53, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Password";
			// 
			// PasswordTextBox
			// 
			this->PasswordTextBox->Location = System::Drawing::Point(395, 121);
			this->PasswordTextBox->Name = L"PasswordTextBox";
			this->PasswordTextBox->PasswordChar = '*';
			this->PasswordTextBox->Size = System::Drawing::Size(140, 20);
			this->PasswordTextBox->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(340, 46);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(29, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Host";
			// 
			// HostTextBox
			// 
			this->HostTextBox->Location = System::Drawing::Point(395, 43);
			this->HostTextBox->Name = L"HostTextBox";
			this->HostTextBox->Size = System::Drawing::Size(140, 20);
			this->HostTextBox->TabIndex = 9;
			// 
			// TestButton
			// 
			this->TestButton->Location = System::Drawing::Point(343, 164);
			this->TestButton->Name = L"TestButton";
			this->TestButton->Size = System::Drawing::Size(75, 23);
			this->TestButton->TabIndex = 11;
			this->TestButton->Text = L"Test";
			this->TestButton->UseVisualStyleBackColor = true;
			this->TestButton->Click += gcnew System::EventHandler(this, &ServerCredentials::TestButton_Click);
			// 
			// SaveButton
			// 
			this->SaveButton->Location = System::Drawing::Point(460, 164);
			this->SaveButton->Name = L"SaveButton";
			this->SaveButton->Size = System::Drawing::Size(75, 23);
			this->SaveButton->TabIndex = 12;
			this->SaveButton->Text = L"Save";
			this->SaveButton->UseVisualStyleBackColor = true;
			this->SaveButton->Click += gcnew System::EventHandler(this, &ServerCredentials::SaveButton_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(5, 7);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(332, 187);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 13;
			this->pictureBox1->TabStop = false;
			// 
			// ServerCredentials
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(559, 206);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->SaveButton);
			this->Controls->Add(this->TestButton);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->HostTextBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->PasswordTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->UserTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->PortTextBox);
			this->Name = L"ServerCredentials";
			this->Text = L"ServerCredentials";
			this->Load += gcnew System::EventHandler(this, &ServerCredentials::ServerCredentials_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SaveButton_Click(System::Object^  sender, System::EventArgs^  e) {
		String^ fileName = "Server_Credentials.txt";

		StreamWriter^ sw = gcnew StreamWriter(fileName);
		sw->Write(conString);
		sw->Close();
		MessageBox::Show("Datele au fost salvate cu succes!");
		this->Close();

	}
private: System::Void TestButton_Click(System::Object^  sender, System::EventArgs^  e) {
	
	conString = "datasource="+HostTextBox->Text+";port="+PortTextBox->Text+";username="+UserTextBox->Text+";password="+PasswordTextBox->Text+";";
	
	try
	{
		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		conDataBase->Open();
		MessageBox::Show("Test reusit!");
		SaveButton->Enabled=true;
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}
}
private: System::Void ServerCredentials_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
