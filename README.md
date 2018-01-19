
# FARC(**F**ind **A**nd **R**eplace **C**omponent)   
>This is a simple program used to updating macro in *.report files which created by APF Formatter.(product of Applied Materials)    
- - -

## Intoduction
If you update a macro(Let's call it macro_v0.0) which is used in several other reports, you have to save this new macro as a new file(macro_v1.0). And then open each reports which use macro_v0.0 and switch to new macro_v1.0, and then save this report. This procedure will call compiler implicitly to re-compile your report so that it can call new macro correctly. This whole procedure may cost 2~3 minutes for each report, depends on your device. Normally, we will have more than 50 files need to be updated. **Now you can do this more quickly through FARC.**

- - -

## Method
If you had opened the *.report file in plain text file. You would find that *.report files are consisted by two parts.
- XML description part.
        Describe the relationship between blocks.
- Function declaration part
        This part looks like function prototype, it is automatically generated by compiler.

So, as you think, as long as we have **XML description part**, we can save and compile this report to generate a executable report which can be put on server directly. The procedure of this program is very simple.

1. Alter the XML part of report.
2. Call compiler and save.
3. Deploy to all server.

For safety and convenience reasons, we add some functions and breakdown some functions into severals.
- - -

## How to use
In this paragraph, I will explain how to call these functions in our program. All you have to prepare is only **cmd**.(command line)
- Copy all currently in use rules.

        syntax: FARC -CopyAllRule    
    This function help us to backup all currently in use reports which are listed in station.cfg. All the reports would be copied to the Input folder.

- Switch component to new one

        Syntax: FARC -Change [old macro] [new macro]    
    It equals to alter all the [old macro] string to [new macro] string in report file. The altered file would be save as a new file with same name in output folder.

- Compile all rule

        syntax: FARC -Compile
    This function will call the report compiler, quintc, which is provided by APF. Recompile all reports in output folder and save. This makes each report a executable report.

- Deploy

        Syntax: FARC -Deploy
    This command can deploy all compiled report to all production server. And the server list is a configure file which is defined in ServerList.txt
- - -

## Restriction
- The path of $APFHOME should be at **C:\apfhome\\**, or this program can not find the station.cfg and the rules listed in it.
- Remember to copy the new macro to all production server before you -Deploy all compiled report to all server.
- Do not use -Deploy command before -Compile, or you will upload unexecutable reports to all production server.
---

## About Author
Po-Jyun Chiou, from Taiwan,have 2.5 year experience in United Microelectronics Corporation(UMC, a semiconductor manufacturing company). Developing RTD rules and optimization algorithm.
