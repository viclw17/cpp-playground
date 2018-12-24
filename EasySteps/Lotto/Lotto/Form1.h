#pragma once
#include <cstdlib> // random
#include <ctime> // time

namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  getBtn;
	protected:
	private: System::Windows::Forms::Button^  resetBtn;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::PictureBox^  pictureBox1;


	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->getBtn = (gcnew System::Windows::Forms::Button());
			this->resetBtn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// getBtn
			// 
			this->getBtn->AutoSize = true;
			this->getBtn->Location = System::Drawing::Point(141, 71);
			this->getBtn->Name = L"getBtn";
			this->getBtn->Size = System::Drawing::Size(128, 23);
			this->getBtn->TabIndex = 0;
			this->getBtn->Text = L"Get My Lucky Numbers";
			this->getBtn->UseVisualStyleBackColor = true;
			this->getBtn->Click += gcnew System::EventHandler(this, &Form1::getBtn_Click);
			// 
			// resetBtn
			// 
			this->resetBtn->Location = System::Drawing::Point(288, 71);
			this->resetBtn->Name = L"resetBtn";
			this->resetBtn->Size = System::Drawing::Size(75, 23);
			this->resetBtn->TabIndex = 1;
			this->resetBtn->Text = L"Reset";
			this->resetBtn->UseVisualStyleBackColor = true;
			this->resetBtn->Click += gcnew System::EventHandler(this, &Form1::resetBtn_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(124, 31);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"label1";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(167, 31);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(35, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"label2";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(210, 31);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"label3";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(253, 31);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"label4";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(296, 31);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(35, 13);
			this->label5->TabIndex = 6;
			this->label5->Text = L"label5";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(339, 31);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 13);
			this->label6->TabIndex = 7;
			this->label6->Text = L"label6";
			// 
			// pictureBox1
			// 
			// add image
			this->pictureBox1->Image = Image::FromFile("d:\\Git\\cpp-playground\\EasySteps\\Lotto\\coder.bmp");
			this->pictureBox1->Location = System::Drawing::Point(17, 14);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(96, 97);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 8;
			this->pictureBox1->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(387, 123);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->resetBtn);
			this->Controls->Add(this->getBtn);
			this->Name = L"Form1";
			this->Text = L"Lotto Number Generator";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// on load
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		Clear();
		srand((int)time(0));
	}
	// clear function
	private: System::Void Clear()
	{
		this->label1->Text = "...";
		this->label2->Text = "...";
		this->label3->Text = "...";
		this->label4->Text = "...";
		this->label5->Text = "...";
		this->label6->Text = "...";

		this->getBtn->Enabled = true;
		this->resetBtn->Enabled = false;
	}
	// reset button
	private: System::Void resetBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		Clear();
	}
	// get random nums button
	private: System::Void getBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		int i, j, k, nums[50];
		for (i = 1; i < 50; i++) nums[i] = i;
		for (i = 1; i < 50; i++) {
			j = (rand() % 49) + 1;
			k = nums[i];
			nums[i] = nums[j];
			nums[j] = k;
		}
		this->label1->Text = Convert::ToString(nums[1]);
		this->label2->Text = Convert::ToString(nums[2]);
		this->label3->Text = Convert::ToString(nums[3]);
		this->label4->Text = Convert::ToString(nums[4]);
		this->label5->Text = Convert::ToString(nums[5]);
		this->label6->Text = Convert::ToString(nums[6]);

		this->getBtn->Enabled = false;
		this->resetBtn->Enabled = true;
	}
};
}
