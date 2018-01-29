#pragma once
int i=0;
#include <boost/timer/timer.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <time.h>
#include <math.h>
#include <string>
#include <fstream>
#include <vector>
#include "Stepper.hpp"
using namespace System::IO;
using namespace System::IO::Ports;
#define BOOST_THREAD_USE_DLL
boost::timer::cpu_timer timer;
std::vector<double> xs,vals;
std::string MotorPortName;
Stepper Silnik("CCC");
double begin=0;
double end=0;
bool finishedrun=false;
int stepsperpoint=1;
void MarshalString ( System::String ^ s, std::string& os ) {
	using namespace System::Runtime::InteropServices;
	const char* chars = 
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}

void MarshalString ( System::String ^ s, std::wstring& os ) {
	using namespace System::Runtime::InteropServices;
	const wchar_t* chars = 
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}

bool ready=false; // Is measurement value ready?
double BoxCarVal; // Measured value
//long int StepNum=0; 
namespace Escort {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
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
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	protected: 
	private: System::Windows::Forms::Timer^  timer1;
	private: System::IO::Ports::SerialPort^  BoxCar;




	private: System::Windows::Forms::Button^  RunButton;
	private: System::Windows::Forms::Button^  PauseButt;
	private: System::Windows::Forms::Button^  ResetButton;
	private: System::Windows::Forms::ComboBox^  BoxCarBox;




	private: System::Windows::Forms::Button^  ScanButton;
	private: System::Windows::Forms::Label^  label1;



	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Button^  ABut;
	private: System::Windows::Forms::TextBox^  textBox1;



	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  NMBPLSLBL;
	private: System::Windows::Forms::ToolStripStatusLabel^  StanLBL;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  MotorBox;
	private: System::IO::Ports::SerialPort^  Motor;
	private: System::Windows::Forms::TextBox^  BeginTB;
	private: System::Windows::Forms::TextBox^  EndTB;


	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::ListBox^  listBox2;







	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->BoxCar = (gcnew System::IO::Ports::SerialPort(this->components));
			this->RunButton = (gcnew System::Windows::Forms::Button());
			this->PauseButt = (gcnew System::Windows::Forms::Button());
			this->ResetButton = (gcnew System::Windows::Forms::Button());
			this->BoxCarBox = (gcnew System::Windows::Forms::ComboBox());
			this->ScanButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->ABut = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->NMBPLSLBL = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->StanLBL = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->MotorBox = (gcnew System::Windows::Forms::ComboBox());
			this->Motor = (gcnew System::IO::Ports::SerialPort(this->components));
			this->BeginTB = (gcnew System::Windows::Forms::TextBox());
			this->EndTB = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->BeginInit();
			this->statusStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// chart1
			// 
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			this->chart1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->chart1->Location = System::Drawing::Point(0, 0);
			this->chart1->Name = L"chart1";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series1->Color = System::Drawing::Color::Red;
			series1->Name = L"cap";
			this->chart1->Series->Add(series1);
			this->chart1->Size = System::Drawing::Size(698, 596);
			this->chart1->TabIndex = 0;
			this->chart1->Text = L"chart1";
			this->chart1->Click += gcnew System::EventHandler(this, &Form1::chart1_Click);
			// 
			// timer1
			// 
			this->timer1->Interval = 2000;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// BoxCar
			// 
			this->BoxCar->BaudRate = 19200;
			this->BoxCar->PortName = L"COM17";
			this->BoxCar->StopBits = System::IO::Ports::StopBits::Two;
			this->BoxCar->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &Form1::BoxCar_DataReceived);
			// 
			// RunButton
			// 
			this->RunButton->Location = System::Drawing::Point(12, 12);
			this->RunButton->Name = L"RunButton";
			this->RunButton->Size = System::Drawing::Size(75, 23);
			this->RunButton->TabIndex = 1;
			this->RunButton->Text = L"Run";
			this->RunButton->UseVisualStyleBackColor = true;
			this->RunButton->Click += gcnew System::EventHandler(this, &Form1::RunButton_Click);
			// 
			// PauseButt
			// 
			this->PauseButt->Location = System::Drawing::Point(93, 12);
			this->PauseButt->Name = L"PauseButt";
			this->PauseButt->Size = System::Drawing::Size(75, 23);
			this->PauseButt->TabIndex = 2;
			this->PauseButt->Text = L"Pause";
			this->PauseButt->UseVisualStyleBackColor = true;
			this->PauseButt->Click += gcnew System::EventHandler(this, &Form1::PauseButt_Click);
			// 
			// ResetButton
			// 
			this->ResetButton->Location = System::Drawing::Point(174, 12);
			this->ResetButton->Name = L"ResetButton";
			this->ResetButton->Size = System::Drawing::Size(75, 23);
			this->ResetButton->TabIndex = 3;
			this->ResetButton->Text = L"Reset";
			this->ResetButton->UseVisualStyleBackColor = true;
			this->ResetButton->Click += gcnew System::EventHandler(this, &Form1::ResetButton_Click);
			// 
			// BoxCarBox
			// 
			this->BoxCarBox->FormattingEnabled = true;
			this->BoxCarBox->Location = System::Drawing::Point(12, 573);
			this->BoxCarBox->Name = L"BoxCarBox";
			this->BoxCarBox->Size = System::Drawing::Size(75, 21);
			this->BoxCarBox->TabIndex = 4;
			// 
			// ScanButton
			// 
			this->ScanButton->Location = System::Drawing::Point(12, 531);
			this->ScanButton->Name = L"ScanButton";
			this->ScanButton->Size = System::Drawing::Size(75, 23);
			this->ScanButton->TabIndex = 6;
			this->ScanButton->Text = L"Scan Ports";
			this->ScanButton->UseVisualStyleBackColor = true;
			this->ScanButton->Click += gcnew System::EventHandler(this, &Form1::ScanButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(9, 557);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"BoxCar";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 41);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Save";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// ABut
			// 
			this->ABut->Location = System::Drawing::Point(93, 531);
			this->ABut->Name = L"ABut";
			this->ABut->Size = System::Drawing::Size(75, 23);
			this->ABut->TabIndex = 9;
			this->ABut->Text = L"Assign";
			this->ABut->UseVisualStyleBackColor = true;
			this->ABut->Click += gcnew System::EventHandler(this, &Form1::ABut_Click);
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::Window;
			this->textBox1->Location = System::Drawing::Point(12, 69);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(236, 174);
			this->textBox1->TabIndex = 11;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->NMBPLSLBL, this->StanLBL, 
				this->toolStripProgressBar1});
			this->statusStrip1->Location = System::Drawing::Point(0, 604);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(964, 22);
			this->statusStrip1->TabIndex = 14;
			this->statusStrip1->Text = L"statusStrip1";
			this->statusStrip1->ItemClicked += gcnew System::Windows::Forms::ToolStripItemClickedEventHandler(this, &Form1::statusStrip1_ItemClicked);
			// 
			// NMBPLSLBL
			// 
			this->NMBPLSLBL->Name = L"NMBPLSLBL";
			this->NMBPLSLBL->Size = System::Drawing::Size(37, 17);
			this->NMBPLSLBL->Text = L"Pulses";
			// 
			// StanLBL
			// 
			this->StanLBL->Name = L"StanLBL";
			this->StanLBL->Size = System::Drawing::Size(25, 17);
			this->StanLBL->Text = L"N/A";
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Maximum = 1000;
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(300, 16);
			this->toolStripProgressBar1->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(90, 557);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(34, 13);
			this->label2->TabIndex = 15;
			this->label2->Text = L"Motor";
			// 
			// MotorBox
			// 
			this->MotorBox->FormattingEnabled = true;
			this->MotorBox->Location = System::Drawing::Point(93, 573);
			this->MotorBox->Name = L"MotorBox";
			this->MotorBox->Size = System::Drawing::Size(75, 21);
			this->MotorBox->TabIndex = 16;
			// 
			// BeginTB
			// 
			this->BeginTB->Location = System::Drawing::Point(12, 264);
			this->BeginTB->Name = L"BeginTB";
			this->BeginTB->Size = System::Drawing::Size(77, 20);
			this->BeginTB->TabIndex = 17;
			// 
			// EndTB
			// 
			this->EndTB->Location = System::Drawing::Point(164, 264);
			this->EndTB->Name = L"EndTB";
			this->EndTB->Size = System::Drawing::Size(87, 20);
			this->EndTB->TabIndex = 18;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 248);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(29, 13);
			this->label3->TabIndex = 19;
			this->label3->Text = L"Start";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(198, 248);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(26, 13);
			this->label4->TabIndex = 20;
			this->label4->Text = L"End";
			// 
			// panel1
			// 
			this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->panel1->Controls->Add(this->chart1);
			this->panel1->Location = System::Drawing::Point(254, 5);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(698, 596);
			this->panel1->TabIndex = 21;
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Items->AddRange(gcnew cli::array< System::Object^  >(6) {L"200", L"250", L"333", L"500", L"1000", L"2000"});
			this->listBox1->Location = System::Drawing::Point(12, 430);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(120, 95);
			this->listBox1->TabIndex = 22;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(15, 414);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(73, 13);
			this->label5->TabIndex = 23;
			this->label5->Text = L"Step time [ms]";
			// 
			// listBox2
			// 
			this->listBox2->FormattingEnabled = true;
			this->listBox2->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"0.5", L"1", L"2", L"5", L"10"});
			this->listBox2->Location = System::Drawing::Point(95, 264);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(63, 69);
			this->listBox2->TabIndex = 24;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(964, 626);
			this->Controls->Add(this->listBox2);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->EndTB);
			this->Controls->Add(this->BeginTB);
			this->Controls->Add(this->MotorBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->ABut);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ScanButton);
			this->Controls->Add(this->BoxCarBox);
			this->Controls->Add(this->ResetButton);
			this->Controls->Add(this->PauseButt);
			this->Controls->Add(this->RunButton);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->chart1))->EndInit();
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void chart1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				 this->timer1->Enabled=false;
				 double x;
				 x=begin+Silnik.StepNum*0.5;
				 StanLBL->Text="Krok "+i.ToString();
				 std::cout << " Krok " << i << std::endl;
				 BoxCar->Write("?1\r"); // Whats the value of analog input 1?
				 toolStripProgressBar1->Value=(int)floor(1000*Silnik.StepNum/(2*(end-begin)));
				 std::cout << "Progress " << (int)floor(1000 * Silnik.StepNum / (2 * (end - begin)))<<std::endl;
				 boost::timer::cpu_timer tkrok;
				 while (!ready&&tkrok.elapsed().wall<5e7){
				 }
				 if (ready) {
					 xs.push_back(x);
					 vals.push_back(BoxCarVal);
					 std::cout<<x<<" "<<BoxCarVal<<std::endl;
					 if (i%10==0){
						 this->chart1->Series[0]->Points->AddXY(x,BoxCarVal);
					 }
					 ready=false;
				 }
				 std::cout << "X bez warunku " << x << std::endl;
				 if (!finishedrun&&!(x==end)) Silnik.Step(stepsperpoint);
				// std::string text="0"+boost::lexical_cast<std::string>((Silnik.StepNum%4)+1);//.ToString();
				 //Silnik.Send(text);

//				 Motor->Write(text);
				 //Silnik.StepNum++;
				 i++;
				 if (x==end) 
				 {
					 timer1->Enabled=false;
					 textBox1->BackColor=Color::FromName("LimeGreen");
					 Silnik.Finish();
					 finishedrun=true;
	//				 Motor->Write("0");
				 }
				
				 std::cout<<x<<" "<<timer.elapsed().wall/1e9<<std::endl;
				 if (!finishedrun) this->timer1->Enabled=true;
			 }

	private: System::Void RunButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 ABut->Enabled=false;
				 MarshalString (MotorBox->Text, MotorPortName);
				 Silnik.Initialize(MotorPortName);
				 BoxCar->NewLine="\r";
				 BoxCar->Open();
//				 Motor->Open();
				 std::cout<<"Ports are open"<<std::endl;
				 BoxCar->Write("W0\r"); // Set delay to 0
				 double::TryParse(BeginTB->Text,begin);
				 double::TryParse(EndTB->Text,end);
				 String^ curItem = listBox1->SelectedItem->ToString();
				 int inter;
				 int::TryParse(curItem, inter);
				 String^ curstep = listBox2->SelectedItem->ToString();
				 double steps;
				 double::TryParse(curstep, steps);
				 int stepsperpnt=(int)(2*steps);
				 if (stepsperpnt!=0) stepsperpoint=stepsperpnt;
				 //std::cout<<inter<<std::endl;
				 if (inter!=0) this->timer1->Interval=inter;
				 this->timer1->Enabled=true;
				 Silnik.StepNum=0;
				 timer.start();
				 std::cout << "The fun begins" <<std::endl;
				 //timer1_Tick(sender,e);
			 }
	private: System::Void ResetButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->chart1->Series[0]->Points->Clear();
			 }
	private: System::Void ScanButton_Click(System::Object^  sender, System::EventArgs^  e) {
				 for each (String^ s in System::IO::Ports::SerialPort::GetPortNames()) 
				 {
					 this->BoxCarBox->Items->Add(s);
					 this->MotorBox->Items->Add(s);
				 } 
			 }
	private: System::Void BoxCar_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) {
				 double value;
				 String^ line=BoxCar->ReadLine();
				 Double::TryParse(line,value);
				 BoxCarVal=value;
				 ready=true;
			 }
	private: System::Void PauseButt_Click(System::Object^  sender, System::EventArgs^  e) {
				 timer1->Enabled=!(timer1->Enabled);
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (saveFileDialog1->ShowDialog() == ::System::Windows::Forms::DialogResult::OK ){
					 StreamWriter^ sw = gcnew StreamWriter(saveFileDialog1->FileName+".dat");
					 int size=xs.size();//chart1->Series[0]->Points->Count;
					 for (i=0;i<size;i++){
						 sw->WriteLine(xs[i].ToString()+" "+vals[i].ToString());
						 //chart1->Series[0]->Points[i]->XValue.ToString()+" "+chart1->Series[0]->Points[i]->YValues[0].ToString()+" "+chart1->Series[1]->Points[i]->YValues[0].ToString());
					 }
					 sw->Close();
				 }
			 }
	private: System::Void ABut_Click(System::Object^  sender, System::EventArgs^  e) {
				 BoxCar->PortName=BoxCarBox->Text;
				 Motor->PortName=MotorBox->Text;
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 std::string BoxCarport, Motorport,beginstr,endstr,interv,steps;
				 std::ifstream inpfile("ports.cfg");
				 timer.stop();
				 if(inpfile>>BoxCarport>>Motorport>>beginstr>>endstr>>interv>>steps){
					 BoxCarBox->Text=gcnew String(BoxCarport.c_str());
					 MotorBox->Text=gcnew String(Motorport.c_str());
					 BeginTB->Text=gcnew String(beginstr.c_str());
					 EndTB->Text=gcnew String(endstr.c_str());
					 if (BoxCarBox->Text!="") BoxCar->PortName=BoxCarBox->Text;
					 if (MotorBox->Text!="") Motor->PortName=MotorBox->Text;
					 int index = listBox1->FindString(gcnew String(interv.c_str()));
					 if ( index != -1 ) listBox1->SetSelected( index, true );
					 int index2 = listBox2->FindString(gcnew String(steps.c_str()));
					 if ( index2 != -1 ) listBox2->SetSelected( index2, true );

				 }
			 }
	private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
				 System::IO::StreamWriter^ sw=gcnew System::IO::StreamWriter("ports.cfg");
				 sw->WriteLine(BoxCarBox->Text+" "+MotorBox->Text+" "+BeginTB->Text+" "+EndTB->Text+" "+listBox1->SelectedItem->ToString()+" "+listBox2->SelectedItem->ToString());
				 sw->Close();
				 if(BoxCar->IsOpen) BoxCar->Close();
				 if(Motor->IsOpen){ 
					 Motor->Write("0");
					 Motor->Close();
				 }
			 }

	private: System::Void statusStrip1_ItemClicked(System::Object^  sender, System::Windows::Forms::ToolStripItemClickedEventArgs^  e) {
			 }
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
			 };
	}

