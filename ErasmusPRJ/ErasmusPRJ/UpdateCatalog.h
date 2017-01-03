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
	/// Summary for UpdateCatalog
	/// </summary>
	public ref class UpdateCatalog : public System::Windows::Forms::Form
	{
	public:
		UpdateCatalog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		UpdateCatalog(int id, String^ name)
		{
			InitializeComponent();
			idToEdit = id;
			nameToEdit = name;
			populate();
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UpdateCatalog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  UpdateButton;
	protected:
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  CodTextBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  ECTSTextBox;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  NumeTextBox;
	
			 //functii
	private:
		void populate()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.catalog where ID=" + idToEdit + ";", conDataBase);
			MySqlDataReader^ myReader;

			try
			{
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();
				myReader->Read();
				NumeTextBox->Text = myReader->GetString("Nume_curs");
				CodTextBox->Text = myReader->GetString("Cod_curs");
				ECTSTextBox->Text = myReader->GetString("ECTS");
				studenti = myReader->GetString("Studenti");
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}
		void updateCourses(String^ courseName)//+imbunatatire: accesare studenti dupa campul Studenti
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ selectDataBase = gcnew MySqlCommand("select * from erasmus.elevi;", conDataBase);
			MySqlDataReader^ myReader;
			//Variabile
			bool found;
			int index;
			int elevi[80];
			array<String^>^ catalog = gcnew array<String^>(80);
			int n = 0;
			String^ courses;
			//

			courseName = courseName + "/";
			try
			{
				conDataBase->Open();
				myReader = selectDataBase->ExecuteReader();
				while (myReader->Read())
				{
					courses = myReader->GetString("Catalog");
					found = courses->Contains(courseName);
					if (found)
					{
						index = courses->IndexOf(courseName);
						catalog[n] = courses->Remove(index, courseName->Length);
						catalog[n] = catalog[n] + NumeTextBox->Text + "/";
						elevi[n++] = myReader->GetInt32("ID");
					}//salveaza elevii care sunt inscrisi la cursul respectiv
				}
				conDataBase->Close();
				myReader->Close();
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}

			conDataBase->Open();
			MySqlDataReader^ update;
			for (int i = 0; i < n; i++)
			{
				try
				{
					MySqlCommand^ updateDataBase = gcnew MySqlCommand("update erasmus.elevi SET Catalog='" + catalog[i] + "' where ID=" + elevi[i] + ";", conDataBase);
					update = updateDataBase->ExecuteReader();
					update->Read();
					update->Close();
				}//sterge cursul respectiv de la elevi
				catch (Exception^ ex)
				{
					MessageBox::Show(ex->Message);
				}
			}
			conDataBase->Close();

		}
	private:
		/// <summary>
		String^ conString = L"datasource=localhost;port=3306;username=root;password=bobcrisaudir8;";
		int idToEdit;
		String^ nameToEdit;
		String^ studenti;
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
			this->CodTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->ECTSTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->NumeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// UpdateButton
			// 
			this->UpdateButton->Location = System::Drawing::Point(204, 202);
			this->UpdateButton->Name = L"UpdateButton";
			this->UpdateButton->Size = System::Drawing::Size(105, 37);
			this->UpdateButton->TabIndex = 14;
			this->UpdateButton->Text = L"Update";
			this->UpdateButton->UseVisualStyleBackColor = true;
			this->UpdateButton->Click += gcnew System::EventHandler(this, &UpdateCatalog::UpdateButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(13, 71);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(26, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"Cod";
			// 
			// CodTextBox
			// 
			this->CodTextBox->Location = System::Drawing::Point(71, 68);
			this->CodTextBox->Name = L"CodTextBox";
			this->CodTextBox->Size = System::Drawing::Size(222, 20);
			this->CodTextBox->TabIndex = 12;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(13, 116);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 11;
			this->label2->Text = L"ECTS";
			// 
			// ECTSTextBox
			// 
			this->ECTSTextBox->Location = System::Drawing::Point(71, 113);
			this->ECTSTextBox->Name = L"ECTSTextBox";
			this->ECTSTextBox->Size = System::Drawing::Size(38, 20);
			this->ECTSTextBox->TabIndex = 10;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(13, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Nume";
			// 
			// NumeTextBox
			// 
			this->NumeTextBox->Location = System::Drawing::Point(71, 23);
			this->NumeTextBox->Name = L"NumeTextBox";
			this->NumeTextBox->Size = System::Drawing::Size(222, 20);
			this->NumeTextBox->TabIndex = 8;
			// 
			// UpdateCatalog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(317, 251);
			this->Controls->Add(this->UpdateButton);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->CodTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->ECTSTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->NumeTextBox);
			this->Name = L"UpdateCatalog";
			this->Text = L"UpdateCatalog";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void UpdateButton_Click(System::Object^  sender, System::EventArgs^  e) {
		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("update erasmus.catalog SET Nume_curs='" + NumeTextBox->Text + "',Cod_curs='" + CodTextBox->Text + "',ECTS=" + System::Convert::ToInt32(ECTSTextBox->Text) + " where ID=" + idToEdit + ";", conDataBase);
		MySqlDataReader^ updateReader;
		
		try
		{
			
			if ((!NumeTextBox->Text->Equals(nameToEdit)) && (studenti->Length>1)) updateCourses(nameToEdit);
			conDataBase->Open();
			updateReader = cmdDataBase->ExecuteReader();
			updateReader->Read();
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
