#include "CutflowPrinter.h"


using namespace std;


int main( int nargs, char ** args )
{
	string infilename = args[1];
	string cutflowfilename = args[2];
	string rootfilename = args[3];
	string textfilename = args[4];
	CutflowPrinter printer( infilename );
	printer.SetCutflowListFileName( cutflowfilename );
	printer.SetOutRootFileName( rootfilename );
	printer.SetOutTextFileName( textfilename );
	printer.Initialize();
	printer.ReadCutflow();
	printer.WriteToRoot();
	printer.WriteToText();	
	
}
