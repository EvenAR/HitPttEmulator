#pragma once
#include <iostream>
#include <string.h>
#include <windows.h>


namespace HidPttEmulator {
	struct KEYINFO {
		int scancode;
		bool extended;
	};

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		KEYINFO * emulationKey;
		;
	private: System::Windows::Forms::Label^  label1;
	public:
		MyForm(void)
		{
			emulationKey = new KEYINFO();
			InitializeComponent();
		}

		void onPttPressed()
		{
			pttIndicator->BackColor = System::Drawing::Color::LightGreen;
		}

		void onPttReleased()
		{
			pttIndicator->BackColor = System::Drawing::Color::DarkGreen;
		}

		void onPttDeviceLost() {
			pttIndicator->BackColor = System::Drawing::Color::Red;
		}

		void onPttDeviceConnected() {
			pttIndicator->BackColor = System::Drawing::Color::DarkGreen;
		}

		void addItemToList(String^ serial)
		{
			//comboBox1->Items->Add(serial);
		}

		KEYINFO* getSelectedEmulationKey()
		{
			return emulationKey;
		}



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::Button^  setKeyButton;
	protected:
	public: System::Windows::Forms::TextBox^  textBox1;
	public: System::Windows::Forms::Panel^  pttIndicator;
	public: System::Windows::Forms::ComboBox^  comboBox2;
	public: System::Windows::Forms::RadioButton^  radioButton1;
	public: System::Windows::Forms::RadioButton^  radioButton2;



	protected:

	protected:











	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::GroupBox^  groupBox1;


	private:
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->setKeyButton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->pttIndicator = (gcnew System::Windows::Forms::Panel());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// setKeyButton
			// 
			this->setKeyButton->Location = System::Drawing::Point(197, 15);
			this->setKeyButton->Name = L"setKeyButton";
			this->setKeyButton->Size = System::Drawing::Size(56, 23);
			this->setKeyButton->TabIndex = 2;
			this->setKeyButton->Text = L"Set key";
			this->setKeyButton->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(86, 16);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(105, 20);
			this->textBox1->TabIndex = 3;
			// 
			// pttIndicator
			// 
			this->pttIndicator->BackColor = System::Drawing::Color::Red;
			this->pttIndicator->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pttIndicator->Location = System::Drawing::Point(79, 88);
			this->pttIndicator->Name = L"pttIndicator";
			this->pttIndicator->Size = System::Drawing::Size(24, 10);
			this->pttIndicator->TabIndex = 8;
			// 
			// comboBox2
			// 
			this->comboBox2->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox2->Enabled = false;
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"F21", L"F22", L"F23", L"F24" });
			this->comboBox2->Location = System::Drawing::Point(86, 45);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(51, 21);
			this->comboBox2->TabIndex = 9;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(9, 19);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(60, 17);
			this->radioButton1->TabIndex = 11;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Custom";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(9, 46);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(76, 17);
			this->radioButton2->TabIndex = 12;
			this->radioButton2->Text = L"Predefined";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(14, 86);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(59, 13);
			this->label3->TabIndex = 13;
			this->label3->Text = L"PTT status";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->setKeyButton);
			this->groupBox1->Controls->Add(this->comboBox2);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Location = System::Drawing::Point(7, 5);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(264, 75);
			this->groupBox1->TabIndex = 14;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Emulate";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(243, 86);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(28, 13);
			this->label1->TabIndex = 15;
			this->label1->Text = L"v2.0";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(279, 106);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->pttIndicator);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->KeyPreview = true;
			this->Name = L"MyForm";
			this->Text = L"HID PTT Emulator";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	};

};
