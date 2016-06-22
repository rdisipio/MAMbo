{
 gROOT->ProcessLine( ".L WjetsSFDumper.C" );
 WjetsSFDumper dumper;
 dumper.Initialize();
 dumper.DumpSF();
}