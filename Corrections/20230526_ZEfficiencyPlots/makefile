

default: TestRunSystematics

TestRun: Execute
	./Execute

TestRunSystematics: ExecuteSystematics
	./ExecuteSystematics

Execute: MakePlot.cpp
	CompileRootMacro MakePlot.cpp Execute

ExecuteSystematics: DeriveSystematics.cpp
	CompileRootMacro DeriveSystematics.cpp ExecuteSystematics
