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
	/// Summary for UpdateStudent
	/// </summary>
	public ref class UpdateStudent : public System::Windows::Forms::Form
	{
	public:
		UpdateStudent(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		UpdateStudent(String^ editString,System::Windows::Forms::Form^ ers)
		{
			InitializeComponent();
			addYears();
			fillSource();
			toEdit = editString;
			populate();
			//erasmus =(ErasmusPRJ::Erasmus^) ers;
		}

	private: System::Windows::Forms::TextBox^  ECTSTextBox;
	public:
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  ObservatiiTextBox;
	private: System::Windows::Forms::CheckedListBox^  CursuriCheckedListBox;
	private: System::Windows::Forms::GroupBox^  SemesterGroupBox;
	private: System::Windows::Forms::RadioButton^  S2RadioButton;
	private: System::Windows::Forms::RadioButton^  S1RadioButton;
	private: System::Windows::Forms::GroupBox^  DataGroupBox;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::TextBox^  TaraTextBox;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  DurataTextBox;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  FacultateTextBox;
	private: System::Windows::Forms::ComboBox^  YearComboBox;
	private: System::Windows::Forms::ComboBox^  MonthComboBox;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::ComboBox^  DayComboBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  MailTextBox;
	private: System::Windows::Forms::TextBox^  CodTextBox;
	private: System::Windows::Forms::TextBox^  PrenumeTextBox;
	private: System::Windows::Forms::TextBox^  NumeTextBox;
			 //private: ErasmusPRJ::Erasmus^ erasmus;
	private: String^ toEdit;
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~UpdateStudent()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::Button^  UpdateButton;
	private: String^ conString = L"datasource=localhost;port=3306;username=root;password=bobcrisaudir8;";


	private:

		void addYears()
		{
			for (int i = 2016; i > (2016 - 80); i--)
			{
				YearComboBox->Items->Add(System::Convert::ToString(i));
			}
		}

		array<String^>^ date;
		void getDate()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select Data_nastere from erasmus.elevi where ID='" + toEdit + "';", conDataBase);
			MySqlDataReader^ myReader;
			String^ toParse;
			

			try
			{
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();
				myReader->Read();

				toParse = myReader->GetString("Data_nastere");
				date = toParse->Split('-');
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

		String^ getCode(String^ uni)
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.universitati where Universitatea='" + uni + "';", conDataBase);
			MySqlDataReader^ myReader;
			String^ toReturn="2";
			
			try
			{
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();
				
				while (myReader->Read())
				{
					toReturn = myReader->GetString("Cod_acord");
					return toReturn;
				}
			}
			catch(Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

		int semester;
		void populate()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.elevi where ID='" + toEdit + "';", conDataBase);
			MySqlDataReader^ myReader;
			String^ uni;
			array<String^>^ courses;

			try {
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();
				
				while (myReader->Read())
				{
					NumeTextBox->Text = myReader->GetString("Nume");
					PrenumeTextBox->Text = myReader->GetString("Prenume");

					getDate();
					DayComboBox->Text = date[2];
					MonthComboBox->Text = date[1];
					YearComboBox->Text = date[0];
					TaraTextBox->Text = myReader->GetString("Tara_provenienta");

					uni = myReader->GetString("Universitate_prov");
					CodTextBox->Text = getCode(uni);

					MailTextBox->Text = myReader->GetString("Mail");
					FacultateTextBox->Text = myReader->GetString("Facultatea");

					DurataTextBox->Text = myReader->GetString("Durata_stagiu");
					ObservatiiTextBox->Text = myReader->GetString("Observatii");

					semester = myReader->GetInt32("Semestru") % 2;
					if (semester==0)
					{
						S2RadioButton->Checked = true;
						S2RadioButton->PerformClick();

					}
					else
					{
						S1RadioButton->Checked = true;
						S1RadioButton->PerformClick();
					}

					//check courses

					courses = myReader->GetString("Catalog")->Split('/');
					for (int i = 0; i < CursuriCheckedListBox->Items->Count; i++)
					{
						CursuriCheckedListBox->SetItemCheckState(i, System::Windows::Forms::CheckState::Unchecked);
						for (int j = 0; j < courses->Length ; j++)
							if (courses[j]->Equals(CursuriCheckedListBox->Items[i]->ToString()))
								CursuriCheckedListBox->SetItemCheckState(i, System::Windows::Forms::CheckState::Checked);
					}

					getECTS();
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

		void getECTS()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.catalog", conDataBase);
			MySqlDataReader^ myReader;
			int sum = 0;

			try
			{
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();

				while (myReader->Read())
				{
					String^ course = "";

					for (int i = 0; i < CursuriCheckedListBox->CheckedItems->Count; i++)
					{
						course = CursuriCheckedListBox->CheckedItems[i]->ToString();
						if (myReader->GetString("Nume_curs")->Equals(course))
							sum += myReader->GetInt32("ECTS");
					}
				}

				ECTSTextBox->Text = System::Convert::ToString(sum);
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
			}
			
		}

		void showCursuri()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.catalog", conDataBase);
			MySqlDataReader^ myReader;
			String^ toParse;
			array<String^>^ code;
			int sem;

			try {
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();

				while (myReader->Read())
				{
					toParse = myReader->GetString("Cod_curs");
					code = toParse->Split('.');
					sem = System::Convert::ToInt32(code[3]);

					sem = sem % 2;
					if (sem == semester)
					{
						CursuriCheckedListBox->Items->Add(myReader->GetString("Nume_curs"));
					}
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}

		}

		String^ getUni()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select Universitatea,Cod_acord from erasmus.universitati", conDataBase);
			MySqlDataReader^ myReader;
			String^ uni = "";

			try {
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();

				while (myReader->Read())
				{
					if (CodTextBox->Text->Equals(myReader->GetString("Cod_acord")))
						uni = myReader->GetString("Universitatea");
				}

				return uni;

			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
			}
		}

		String^ getCourses()//cursurile studentului
		{
			String^ courses = "";

			for (int i = 0; i < CursuriCheckedListBox->CheckedItems->Count; i++)
			{
				courses += CursuriCheckedListBox->CheckedItems[i]->ToString();
				courses += "/";
			}

			return courses;
		}

		void addStudentToCatalog()
		{
			array<String^>^ concatStudents = gcnew array<String^>(40);
			String^ studentToAdd = "";
			int uniID = 1;
			int lastID = System::Convert::ToInt32(toEdit);
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.catalog", conDataBase);
			MySqlCommand^ updateCatalog = gcnew MySqlCommand("update erasmus.catalog SET Studenti='" + studentToAdd + "' where ID=" + uniID + ";", conDataBase);
			MySqlDataReader^ myReader;
			MySqlDataReader^ update;
			int courses[40];
			int k = 0;

			try
			{
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();


				int idCurs;
				while (myReader->Read())
				{
					String^ course = "";

					for (int i = 0; i < CursuriCheckedListBox->CheckedItems->Count; i++)
					{
						course = CursuriCheckedListBox->CheckedItems[i]->ToString();
						idCurs = myReader->GetInt32("ID");
						if (myReader->GetString("Nume_curs")->Equals(course))
						{
							courses[k] = idCurs;
							concatStudents[k++] = myReader->GetString("Studenti");
						}
					}//Pregateste studentii deja existenti la cursul respectiv

				}

				conDataBase->Close();
				myReader->Close();//Se inchide prima conexiune
			}
			catch (Exception^ ex) {
				MessageBox::Show(ex->Message);
			}

			conDataBase->Open();
			String^ stud;
			stud =System::Convert::ToString(lastID) + "/";
			for (int i = 0; i < k; i++)
			{
				try
				{


					studentToAdd = concatStudents[i] + stud;
					uniID = courses[i];
					MySqlCommand^ updateCatalog = gcnew MySqlCommand("update erasmus.catalog SET Studenti='" + studentToAdd + "' where ID=" + uniID + ";", conDataBase);
					update = updateCatalog->ExecuteReader();//comanda trebuie reinitializata pt fiecare curs la care se adauga
					update->Read();							//studentul respectiv
					update->Close();//se inchide reader-ul pentru a putea lua alta comanda
				}
				catch (Exception^ ex)
				{
					MessageBox::Show(ex->Message);
				}
			}
		}

		String^ getTara()
		{
			String^ toParse;
			array<String^>^ code;


			toParse = CodTextBox->Text;
			code = toParse->Split(' ');
			return code[0];

		}

		void fillSource()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.universitati;", conDataBase);
			MySqlDataReader^ myReader;

			try {
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();


				while (myReader->Read())
				{
					CodTextBox->AutoCompleteCustomSource->Add(myReader->GetString("Cod_acord"));
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

		void removeFromCourses()
		{
			MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
			//Variabile{
			String^ studentID = toEdit;
			studentID = studentID + "/";
			array<String^>^ studCatalog = gcnew array<String^>(100);
			String^ studToRemove = "";
			int course[20];
			int n = 0;
			int index;
			bool found;
			//}
			MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.catalog;", conDataBase);
			MySqlDataReader^ myReader;

			try {
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();

				while (myReader->Read())
				{
					studToRemove = myReader->GetString("Studenti");
					found = studToRemove->Contains(studentID);
					if (found)
					{
						index = studToRemove->IndexOf(studentID);
						studCatalog[n] = studToRemove->Remove(index, 3);
						course[n++] = myReader->GetInt32("ID");
					}	//retine cursurile la care e inscris studentul si ii sterge ID-ul
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
			conDataBase->Close();
			myReader->Close();
			//se inchice prima conexiune

			conDataBase->Open();//se deschide conexiunea pentru a updata baza de date
			MySqlDataReader^ update;
			for (int i = 0; i < n; i++) {
				try
				{
					MySqlCommand^ updateDataBase = gcnew MySqlCommand("update erasmus.catalog SET Studenti='" + studCatalog[i] + "' where ID=" + course[i] + ";", conDataBase);
					update = updateDataBase->ExecuteReader();
					update->Read();
					update->Close();//se inchide reader-ul
				}
				catch (Exception^ ex)
				{
					MessageBox::Show(ex->Message);
				}
			}//for pentru a parcurge toate cursurile la care e inscris studentul care trebuie sters;
		}

		/// <summary>
		/// Required designer variable.
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
			this->ECTSTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->ObservatiiTextBox = (gcnew System::Windows::Forms::TextBox());
			this->CursuriCheckedListBox = (gcnew System::Windows::Forms::CheckedListBox());
			this->SemesterGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->S2RadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->S1RadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->DataGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->TaraTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->DurataTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->FacultateTextBox = (gcnew System::Windows::Forms::TextBox());
			this->YearComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->MonthComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->DayComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->MailTextBox = (gcnew System::Windows::Forms::TextBox());
			this->CodTextBox = (gcnew System::Windows::Forms::TextBox());
			this->PrenumeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->NumeTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SemesterGroupBox->SuspendLayout();
			this->DataGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// UpdateButton
			// 
			this->UpdateButton->Location = System::Drawing::Point(428, 408);
			this->UpdateButton->Name = L"UpdateButton";
			this->UpdateButton->Size = System::Drawing::Size(81, 24);
			this->UpdateButton->TabIndex = 13;
			this->UpdateButton->Text = L"Update";
			this->UpdateButton->UseVisualStyleBackColor = true;
			this->UpdateButton->Click += gcnew System::EventHandler(this, &UpdateStudent::UpdateButton_Click);
			// 
			// ECTSTextBox
			// 
			this->ECTSTextBox->Location = System::Drawing::Point(469, 225);
			this->ECTSTextBox->Name = L"ECTSTextBox";
			this->ECTSTextBox->Size = System::Drawing::Size(40, 20);
			this->ECTSTextBox->TabIndex = 27;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(474, 209);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(35, 13);
			this->label10->TabIndex = 26;
			this->label10->Text = L"ECTS";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(9, 247);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(54, 13);
			this->label8->TabIndex = 24;
			this->label8->Text = L"Observatii";
			// 
			// ObservatiiTextBox
			// 
			this->ObservatiiTextBox->Location = System::Drawing::Point(12, 262);
			this->ObservatiiTextBox->Multiline = true;
			this->ObservatiiTextBox->Name = L"ObservatiiTextBox";
			this->ObservatiiTextBox->Size = System::Drawing::Size(498, 140);
			this->ObservatiiTextBox->TabIndex = 25;
			// 
			// CursuriCheckedListBox
			// 
			this->CursuriCheckedListBox->FormattingEnabled = true;
			this->CursuriCheckedListBox->Location = System::Drawing::Point(267, 61);
			this->CursuriCheckedListBox->Name = L"CursuriCheckedListBox";
			this->CursuriCheckedListBox->Size = System::Drawing::Size(201, 184);
			this->CursuriCheckedListBox->TabIndex = 23;
			this->CursuriCheckedListBox->Leave += gcnew System::EventHandler(this, &UpdateStudent::CursuriCheckedListBox_Leave);
			// 
			// SemesterGroupBox
			// 
			this->SemesterGroupBox->Controls->Add(this->S2RadioButton);
			this->SemesterGroupBox->Controls->Add(this->S1RadioButton);
			this->SemesterGroupBox->Location = System::Drawing::Point(267, 12);
			this->SemesterGroupBox->Name = L"SemesterGroupBox";
			this->SemesterGroupBox->Size = System::Drawing::Size(201, 43);
			this->SemesterGroupBox->TabIndex = 22;
			this->SemesterGroupBox->TabStop = false;
			this->SemesterGroupBox->Text = L"SemesterGroupBox";
			// 
			// S2RadioButton
			// 
			this->S2RadioButton->AutoSize = true;
			this->S2RadioButton->Location = System::Drawing::Point(105, 21);
			this->S2RadioButton->Name = L"S2RadioButton";
			this->S2RadioButton->Size = System::Drawing::Size(80, 17);
			this->S2RadioButton->TabIndex = 13;
			this->S2RadioButton->TabStop = true;
			this->S2RadioButton->Text = L"Semestrul 2";
			this->S2RadioButton->UseVisualStyleBackColor = true;
			this->S2RadioButton->CheckedChanged += gcnew System::EventHandler(this, &UpdateStudent::S2RadioButton_CheckedChanged);
			// 
			// S1RadioButton
			// 
			this->S1RadioButton->AutoSize = true;
			this->S1RadioButton->Location = System::Drawing::Point(14, 21);
			this->S1RadioButton->Name = L"S1RadioButton";
			this->S1RadioButton->Size = System::Drawing::Size(80, 17);
			this->S1RadioButton->TabIndex = 12;
			this->S1RadioButton->TabStop = true;
			this->S1RadioButton->Text = L"Semestrul 1";
			this->S1RadioButton->UseVisualStyleBackColor = true;
			this->S1RadioButton->CheckedChanged += gcnew System::EventHandler(this, &UpdateStudent::S1RadioButton_CheckedChanged);
			// 
			// DataGroupBox
			// 
			this->DataGroupBox->Controls->Add(this->label9);
			this->DataGroupBox->Controls->Add(this->TaraTextBox);
			this->DataGroupBox->Controls->Add(this->label7);
			this->DataGroupBox->Controls->Add(this->DurataTextBox);
			this->DataGroupBox->Controls->Add(this->label6);
			this->DataGroupBox->Controls->Add(this->FacultateTextBox);
			this->DataGroupBox->Controls->Add(this->YearComboBox);
			this->DataGroupBox->Controls->Add(this->MonthComboBox);
			this->DataGroupBox->Controls->Add(this->label5);
			this->DataGroupBox->Controls->Add(this->label4);
			this->DataGroupBox->Controls->Add(this->DayComboBox);
			this->DataGroupBox->Controls->Add(this->label3);
			this->DataGroupBox->Controls->Add(this->label2);
			this->DataGroupBox->Controls->Add(this->label1);
			this->DataGroupBox->Controls->Add(this->MailTextBox);
			this->DataGroupBox->Controls->Add(this->CodTextBox);
			this->DataGroupBox->Controls->Add(this->PrenumeTextBox);
			this->DataGroupBox->Controls->Add(this->NumeTextBox);
			this->DataGroupBox->Location = System::Drawing::Point(12, 12);
			this->DataGroupBox->Name = L"DataGroupBox";
			this->DataGroupBox->Size = System::Drawing::Size(249, 232);
			this->DataGroupBox->TabIndex = 21;
			this->DataGroupBox->TabStop = false;
			this->DataGroupBox->Text = L"DataGroupBox";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(5, 124);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(29, 13);
			this->label9->TabIndex = 19;
			this->label9->Text = L"Tara";
			// 
			// TaraTextBox
			// 
			this->TaraTextBox->Location = System::Drawing::Point(69, 121);
			this->TaraTextBox->Name = L"TaraTextBox";
			this->TaraTextBox->Size = System::Drawing::Size(126, 20);
			this->TaraTextBox->TabIndex = 18;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(5, 202);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(39, 13);
			this->label7->TabIndex = 17;
			this->label7->Text = L"Durata";
			// 
			// DurataTextBox
			// 
			this->DurataTextBox->Location = System::Drawing::Point(69, 199);
			this->DurataTextBox->Name = L"DurataTextBox";
			this->DurataTextBox->Size = System::Drawing::Size(126, 20);
			this->DurataTextBox->TabIndex = 16;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(6, 173);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(57, 13);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Facultatea";
			// 
			// FacultateTextBox
			// 
			this->FacultateTextBox->Location = System::Drawing::Point(69, 173);
			this->FacultateTextBox->Name = L"FacultateTextBox";
			this->FacultateTextBox->Size = System::Drawing::Size(126, 20);
			this->FacultateTextBox->TabIndex = 14;
			// 
			// YearComboBox
			// 
			this->YearComboBox->FormattingEnabled = true;
			this->YearComboBox->Location = System::Drawing::Point(176, 69);
			this->YearComboBox->Name = L"YearComboBox";
			this->YearComboBox->Size = System::Drawing::Size(54, 21);
			this->YearComboBox->TabIndex = 12;
			// 
			// MonthComboBox
			// 
			this->MonthComboBox->FormattingEnabled = true;
			this->MonthComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(12) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					L"9", L"10", L"11", L"12"
			});
			this->MonthComboBox->Location = System::Drawing::Point(122, 68);
			this->MonthComboBox->Name = L"MonthComboBox";
			this->MonthComboBox->Size = System::Drawing::Size(48, 21);
			this->MonthComboBox->TabIndex = 13;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(5, 146);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(26, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Mail";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(5, 98);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(26, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Cod";
			// 
			// DayComboBox
			// 
			this->DayComboBox->FormattingEnabled = true;
			this->DayComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(31) {
				L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8",
					L"9", L"10", L"11", L"12", L"13", L"14", L"15", L"16", L"17", L"18", L"19", L"20", L"21", L"22", L"23", L"24", L"25", L"26",
					L"27", L"28", L"29", L"30", L"31"
			});
			this->DayComboBox->Location = System::Drawing::Point(77, 68);
			this->DayComboBox->Name = L"DayComboBox";
			this->DayComboBox->Size = System::Drawing::Size(39, 21);
			this->DayComboBox->TabIndex = 11;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(5, 72);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(66, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Data nasterii";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(5, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(49, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Prenume";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(5, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Nume";
			// 
			// MailTextBox
			// 
			this->MailTextBox->Location = System::Drawing::Point(69, 147);
			this->MailTextBox->Name = L"MailTextBox";
			this->MailTextBox->Size = System::Drawing::Size(126, 20);
			this->MailTextBox->TabIndex = 5;
			// 
			// CodTextBox
			// 
			this->CodTextBox->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::Suggest;
			this->CodTextBox->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->CodTextBox->Location = System::Drawing::Point(69, 95);
			this->CodTextBox->Name = L"CodTextBox";
			this->CodTextBox->Size = System::Drawing::Size(126, 20);
			this->CodTextBox->TabIndex = 4;
			this->CodTextBox->Leave += gcnew System::EventHandler(this, &UpdateStudent::CodTextBox_Leave);
			// 
			// PrenumeTextBox
			// 
			this->PrenumeTextBox->Location = System::Drawing::Point(69, 43);
			this->PrenumeTextBox->Name = L"PrenumeTextBox";
			this->PrenumeTextBox->Size = System::Drawing::Size(126, 20);
			this->PrenumeTextBox->TabIndex = 2;
			// 
			// NumeTextBox
			// 
			this->NumeTextBox->Location = System::Drawing::Point(69, 17);
			this->NumeTextBox->Name = L"NumeTextBox";
			this->NumeTextBox->Size = System::Drawing::Size(126, 20);
			this->NumeTextBox->TabIndex = 1;
			// 
			// UpdateStudent
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(517, 437);
			this->Controls->Add(this->ECTSTextBox);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->ObservatiiTextBox);
			this->Controls->Add(this->CursuriCheckedListBox);
			this->Controls->Add(this->SemesterGroupBox);
			this->Controls->Add(this->DataGroupBox);
			this->Controls->Add(this->UpdateButton);
			this->Name = L"UpdateStudent";
			this->Text = L"UpdateStudent";
			this->Load += gcnew System::EventHandler(this, &UpdateStudent::UpdateStudent_Load);
			this->SemesterGroupBox->ResumeLayout(false);
			this->SemesterGroupBox->PerformLayout();
			this->DataGroupBox->ResumeLayout(false);
			this->DataGroupBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void NumeTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void UpdateButton_Click(System::Object^  sender, System::EventArgs^  e) {
		MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
		String^ dateToAdd = YearComboBox->Text + "-" + MonthComboBox->Text + "-" + DayComboBox->Text;
		MySqlCommand^ cmdDataBase = gcnew MySqlCommand("update erasmus.elevi SET Nume='"+NumeTextBox->Text+"',Prenume='" + PrenumeTextBox->Text + "',Data_nastere='" + dateToAdd + "',Tara_provenienta='" + TaraTextBox->Text + "',Mail='" + MailTextBox->Text + "',Universitate_prov='" + getUni() + "',Catalog='" + getCourses() + "',Durata_stagiu='" + DurataTextBox->Text + "',Semestru='" + System::Convert::ToString(semester) + "',Observatii='" + ObservatiiTextBox->Text + "',Facultatea='" + FacultateTextBox->Text + "' where ID='" + toEdit + "';", conDataBase);
		MySqlDataReader^ myReader;

			try {
				removeFromCourses();
				addStudentToCatalog();
				conDataBase->Open();
				myReader = cmdDataBase->ExecuteReader();
				myReader->Read();
				if (MessageBox::Show("Datele au fost updatate cu succes! Doriti sa continuati?",
					"Add Student", MessageBoxButtons::YesNo,
					MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::No)
				{
					//erasmus->ShowButton->PerformClick();
					this->Close();
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show(ex->Message);
			}
		}

	
private: System::Void UpdateStudent_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void S1RadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	CursuriCheckedListBox->Items->Clear();
	showCursuri();
}
private: System::Void S2RadioButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	CursuriCheckedListBox->Items->Clear();
	showCursuri();
}
private: System::Void CursuriCheckedListBox_Leave(System::Object^  sender, System::EventArgs^  e) {
	getECTS();
}
private: System::Void CodTextBox_Leave(System::Object^  sender, System::EventArgs^  e) {
	MySqlConnection^ conDataBase = gcnew MySqlConnection(conString);
	MySqlCommand^ cmdDataBase = gcnew MySqlCommand("select * from erasmus.tari where Cod_tara='" + getTara() + "';", conDataBase);
	MySqlDataReader^ myReader;
	String^ toParse;
	array<String^>^ code;

	try {
		conDataBase->Open();
		myReader = cmdDataBase->ExecuteReader();

		while (myReader->Read())
		{
			toParse = CodTextBox->Text;
			code = toParse->Split(' ');
			TaraTextBox->Text = myReader->GetString("Nume_tara");
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}
}
};
}