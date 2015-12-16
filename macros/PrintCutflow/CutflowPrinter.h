#ifndef _CUTFLOWPRINTER_H_
#define _CUTFLOWPRINTER_H_
#include <vector>
#include "TH1D.h"
#include "TFile.h"
#include <map>
#include <fstream>
#include <iostream>

class CutflowPrinter
{
	private:
		std::map< std::string, TH1D*> h_cutflows;
		std::vector< std::string > m_cutflowList;
		std::string m_cutflowListFileName;
		std::ifstream m_cutflowListFile;
		std::ifstream m_inFileList;
		std::string m_inFileListName;
		std::vector< std::string > m_inFileNames;
		TFile * m_rootOutFile;
		std::string m_rootOutFileName;
		std::ofstream m_textOutFile;
		std::string m_textOutFileName;
	public:
		CutflowPrinter();
		CutflowPrinter( const std::string& infilename );
		~CutflowPrinter(){};
		void SetInFileListName( const std::string& );
		void SetCutflowListFileName( const std::string& );
		void SetOutRootFileName( const std::string& );
		void SetOutTextFileName( const std::string& );
		void Initialize();
		void ReadCutflow();
		void WriteToRoot();
		void WriteToText();
		
		
		
};


#endif
