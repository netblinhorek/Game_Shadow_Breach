#pragma once

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Registration
	/// </summary>
	public ref class Registration : public System::Windows::Forms::Form
	{
	public:
		Registration(void)
		{
			InitializeComponent();
			LoadBackgroundImage(); // ВЫЗОВИТЕ МЕТОД ЗДЕСЬ
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Registration()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::Label^ labelTitle;
		System::Windows::Forms::Label^ labelName;
		System::Windows::Forms::Label^ labelEmail;
		System::Windows::Forms::Label^ labelPassword;
		System::Windows::Forms::TextBox^ textBoxName;
		System::Windows::Forms::TextBox^ textBoxEmail;
		System::Windows::Forms::TextBox^ textBoxPassword;
		System::Windows::Forms::Button^ buttonRegister;
		System::Windows::Forms::Button^ buttonBack;

		void SaveToCSV(String^ name, String^ email, String^ password)
		{
			try
			{
				String^ csvPath = "visits.csv";
				
				// Читаем существующие строки для подсчета номера
				array<String^>^ lines = {};
				int nextNumber = 1;
				
				if (System::IO::File::Exists(csvPath))
				{
					lines = System::IO::File::ReadAllLines(csvPath);
					// Ищем последний номер
					for (int i = lines->Length - 1; i >= 0; i--)
					{
						if (lines[i]->Trim()->Length > 0 && !lines[i]->StartsWith("Номер"))
						{
							array<String^>^ parts = lines[i]->Split(';');
							if (parts->Length > 0)
							{
								int num;
								if (Int32::TryParse(parts[0], num))
								{
									nextNumber = num + 1;
									break;
								}
							}
						}
					}
				}
				
				// Формируем новую строку с номером
				String^ line = String::Format("{0};{1};{2};{3}", nextNumber, name, email, password);
				
				// Добавляем новую строку
				System::IO::File::AppendAllText(csvPath, line + Environment::NewLine);
				
				MessageBox::Show("Данные успешно сохранены!", "Успех",
					MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка сохранения: " + ex->Message, "Ошибка",
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}

		void LoadBackgroundImage()
		{
			try
			{
				array<String^>^ possiblePaths = {
					"регистрация.gif",
					};

				bool imageLoaded = false;
				for each (String ^ path in possiblePaths)
				{
					if (System::IO::File::Exists(path))
					{
						pictureBox1->Image = Image::FromFile(path);

						if (path->EndsWith(".gif", StringComparison::OrdinalIgnoreCase))
						{
							pictureBox1->SizeMode = PictureBoxSizeMode::Zoom;
						}
						else
						{
							pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;
						}

						pictureBox1->Dock = DockStyle::Fill;
						imageLoaded = true;
						break;
					}
				}

				if (!imageLoaded)
				{
					pictureBox1->BackColor = Color::Black;
					MessageBox::Show("Фоновое изображение не найдено!\nПроверьте наличие файла 'регистрация.gif'", "Предупреждение",
						MessageBoxButtons::OK, MessageBoxIcon::Warning);
				}
			}
			catch (Exception^ ex)
			{
				pictureBox1->BackColor = Color::Black;
				MessageBox::Show("Ошибка загрузки изображения: " + ex->Message,
					"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->labelTitle = (gcnew System::Windows::Forms::Label());
			this->labelName = (gcnew System::Windows::Forms::Label());
			this->labelEmail = (gcnew System::Windows::Forms::Label());
			this->labelPassword = (gcnew System::Windows::Forms::Label());
			this->textBoxName = (gcnew System::Windows::Forms::TextBox());
			this->textBoxEmail = (gcnew System::Windows::Forms::TextBox());
			this->textBoxPassword = (gcnew System::Windows::Forms::TextBox());
			this->buttonRegister = (gcnew System::Windows::Forms::Button());
			this->buttonBack = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();

			// 
			// pictureBox1
			// 
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1359, 793);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->BackColor = Color::Black;

			// 
			// labelTitle
			// 
			this->labelTitle->AutoSize = true;
			this->labelTitle->Font = gcnew System::Drawing::Font("Arial", 36, FontStyle::Bold);
			this->labelTitle->ForeColor = Color::White;
			this->labelTitle->BackColor = Color::Black;
			this->labelTitle->Text = "Регистрация";
			this->labelTitle->Location = Point(350, 100);

			// 
			// labelName
			// 
			this->labelName->AutoSize = true;
			this->labelName->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->labelName->ForeColor = Color::White;
			this->labelName->BackColor = Color::Black;
			this->labelName->Text = "Имя:";
			this->labelName->Location = Point(400, 300);

			// 
			// textBoxName
			// 
			this->textBoxName->Font = gcnew System::Drawing::Font("Arial", 12);
			this->textBoxName->Location = Point(650, 300);
			this->textBoxName->Size = Drawing::Size(300, 30);
			this->textBoxName->BackColor = Color::White;
			this->textBoxName->ForeColor = Color::Black;

			// 
			// labelEmail
			// 
			this->labelEmail->AutoSize = true;
			this->labelEmail->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->labelEmail->ForeColor = Color::White;
			this->labelEmail->BackColor = Color::Black;
			this->labelEmail->Text = "Почта:";
			this->labelEmail->Location = Point(400, 390);

			// 
			// textBoxEmail
			// 
			this->textBoxEmail->Font = gcnew System::Drawing::Font("Arial", 12);
			this->textBoxEmail->Location = Point(650, 390);
			this->textBoxEmail->Size = Drawing::Size(300, 30);
			this->textBoxEmail->BackColor = Color::White;
			this->textBoxEmail->ForeColor = Color::Black;

			// 
			// labelPassword
			// 
			this->labelPassword->AutoSize = true;
			this->labelPassword->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->labelPassword->ForeColor = Color::White;
			this->labelPassword->BackColor = Color::Black;
			this->labelPassword->Text = "Пароль:";
			this->labelPassword->Location = Point(400, 480);
			this->labelPassword->BringToFront();

			// 
			// textBoxPassword
			// 
			this->textBoxPassword->Font = gcnew System::Drawing::Font("Arial", 12);
			this->textBoxPassword->Location = Point(650, 480);
			this->textBoxPassword->Size = Drawing::Size(300, 30);
			this->textBoxPassword->BackColor = Color::White;
			this->textBoxPassword->ForeColor = Color::Black;
			this->textBoxPassword->PasswordChar = '*';

			// 
			// buttonRegister
			// 
			this->buttonRegister->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->buttonRegister->Location = Point(400, 570);
			this->buttonRegister->Size = Drawing::Size(550, 60);
			this->buttonRegister->Text = "Зарегистрироваться";
			this->buttonRegister->BackColor = Color::Black;
			this->buttonRegister->ForeColor = Color::White;
			this->buttonRegister->FlatStyle = FlatStyle::Flat;
			this->buttonRegister->Cursor = Cursors::Hand;
			this->buttonRegister->Click += gcnew System::EventHandler(this, &Registration::buttonRegister_Click);

			// 
			// buttonBack
			// 
			this->buttonBack->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
			this->buttonBack->Location = Point(10, 20);
			this->buttonBack->Size = Drawing::Size(200, 60);
			this->buttonBack->Text = "Назад";
			this->buttonBack->BackColor = Color::Black;
			this->buttonBack->ForeColor = Color::White;
			this->buttonBack->FlatStyle = FlatStyle::Flat;
			this->buttonBack->Cursor = Cursors::Hand;
			this->buttonBack->Click += gcnew System::EventHandler(this, &Registration::buttonBack_Click);

			// 
			// Registration
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1359, 793); 
			this->Controls->Add(this->pictureBox1);
			this->pictureBox1->SendToBack();
			
			// Добавляем элементы управления поверх фона
			this->Controls->Add(this->labelTitle);
			this->Controls->Add(this->labelName);
			this->Controls->Add(this->labelEmail);
			this->Controls->Add(this->labelPassword);
			this->Controls->Add(this->textBoxName);
			this->Controls->Add(this->textBoxEmail);
			this->Controls->Add(this->textBoxPassword);
			this->Controls->Add(this->buttonRegister);
			this->Controls->Add(this->buttonBack);
			
			// Убеждаемся, что все элементы видны поверх фона
			this->labelTitle->BringToFront();
			this->labelName->BringToFront();
			this->labelEmail->BringToFront();
			this->labelPassword->BringToFront();
			this->textBoxName->BringToFront();
			this->textBoxEmail->BringToFront();
			this->textBoxPassword->BringToFront();
			this->buttonRegister->BringToFront();
			this->buttonBack->BringToFront();
			this->Name = L"Registration";
			this->Text = L"Регистрация - Вход";
			this->StartPosition = FormStartPosition::CenterScreen;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
		}

		System::Void buttonRegister_Click(System::Object^ sender, System::EventArgs^ e)
		{
			String^ name = textBoxName->Text->Trim();
			String^ email = textBoxEmail->Text->Trim();
			String^ password = textBoxPassword->Text->Trim();
			
			if (name->Length == 0 || email->Length == 0 || password->Length == 0)
			{
				MessageBox::Show("Пожалуйста, заполните все поля!", "Предупреждение",
					MessageBoxButtons::OK, MessageBoxIcon::Warning);
				return;
			}
			
			SaveToCSV(name, email, password);
			
			// Очищаем поля после сохранения
			textBoxName->Text = "";
			textBoxEmail->Text = "";
			textBoxPassword->Text = "";
		}

		System::Void buttonBack_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->Close();
		}
#pragma endregion
	};
}