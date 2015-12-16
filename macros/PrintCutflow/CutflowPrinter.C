#include "CutflowPrinter.h"
using namespace std;

CutflowPrinter::CutflowPrinter()
{
}

CutflowPrinter::CutflowPrinter( const std::string& infilename )
{
	m_inFileListName = infilename;
}

void CutflowPrinter::SetInFileListName( const std::string& infilename )
{
	m_inFileListName = infilename;
}


void CutflowPrinter::SetCutflowListFileName( const std::string& infilename )
{
	m_cutflowListFileName = infilename;
}



void CutflowPrinter::SetOutRootFileName( const std::string& outfilename )
{
	m_rootOutFileName = outfilename;
}

void CutflowPrinter::SetOutTextFileName( const std::string& outfilename )
{
	m_textOutFileName = outfilename;
}


void CutflowPrinter::Initialize()
{
	cout << "Opening file list " << m_inFileListName << endl;
	m_inFileList.open( m_inFileListName.c_str() );
	string temp;
	int counter = 0;
	while(1)
	{
		m_inFileList >> temp;
		if( m_inFileList.eof() ) break;
		m_inFileNames.push_back( temp );
		counter++;
	}
	cout << "Will loop over " << counter << " root files\n";
	
	cout << "Reading cutflow list from " << m_cutflowListFileName << "\n";
	m_cutflowListFile.open( m_cutflowListFileName.c_str() ); 
	counter = 0;
	while(1)
	{
		m_cutflowListFile >> temp;
		if( m_cutflowListFile.eof() ) break;
		m_cutflowList.push_back( temp );
		counter++;
	}
	cout << counter << " cutflow loaded\n";
	cout << "Tool initialized\n";
}



void CutflowPrinter::ReadCutflow()
{
	int file_counter = 0;
	for( const auto& filename: m_inFileNames )
	{
		int cutflow_counter = 0;
		TFile * f_temp = TFile::Open( filename.c_str() );
		cout << "Loading cutflow from " << filename << endl;
		for( const auto& cutflow: m_cutflowList )
		{
		
			TH1D * h_temp = (TH1D*) f_temp->Get( ( cutflow + "/cutflow" ).c_str() )->Clone();
			h_temp->SetDirectory( 0 );
			if( file_counter == 0 )
			{
				h_temp->SetName( cutflow.c_str() );
				h_temp->SetTitle( cutflow.c_str() );
				h_cutflows[cutflow] = h_temp ;
			}
			else h_cutflows[cutflow]->Add( h_temp );
			cutflow_counter++;
		}
		f_temp->Close();
		delete f_temp;
		file_counter++;
	}
}





void CutflowPrinter::WriteToRoot()
{
	m_rootOutFile = TFile::Open( m_rootOutFileName.c_str(), "RECREATE" );
	for( auto& cutflow: h_cutflows )
	{
		cutflow.second->SetDirectory( m_rootOutFile );
	}
	m_rootOutFile->Write();
}
void CutflowPrinter::WriteToText()
{
	m_textOutFile.open( m_textOutFileName.c_str()  );
	for( const auto& cutflow: h_cutflows )
	{
		m_textOutFile << cutflow.second->GetName() << endl;
		for( int i = 1; i <= cutflow.second->GetNbinsX(); ++i ) m_textOutFile << cutflow.second->GetXaxis()->GetBinLabel(i) << ":\t" << cutflow.second->GetBinContent(i) << endl;
		m_textOutFile << endl;
		m_textOutFile << "======================\n"; 
	}	
}

