{
printf("                                                     ##########################\n");
printf("                                                     ################ #########\n");
printf("                                                     ###############   ########\n");
printf("                                                     ##############  #  #######\n");
printf("                                                     ############### # ########\n");
printf("                                                     ###############   ########\n");
printf("                                                     ##############     #######\n");
printf("                                                     ############         #####\n");
printf("                                                     ###########            ###\n");
printf("                                                                            ###\n");
printf("            #                      #  #    # #   #   *                      ###\n");
printf("                                      #          #   *                       ##\n");
printf("#   # # ##  # #   #  ##  # ##  ### # ###   ###  ###  ****   ***  * **  * **  ##\n");
printf("#   # ##  # # #   # #  # ##   #    #  #       #  #   *   * *   * **  * **  * ##\n");
printf("#   # #   # #  # #  #### #     ##  #  #    ####  #   *   * *   * *   * *   * ##\n");
printf("#  ## #   # #  # #  #    #       # #  #   #  ##  #   *   * *   * *   * *   * ##\n");
printf(" ## # #   # #   #    ### #    ###  #   ##  ## #   ##  ***   ***  *   * *   * ##\n");

printf("\nWelcome to E214 ATLAS\n\nAssignment 2: Electron Calibration");
printf("\nType .q to quit\n\n");
printf("Please load a new calibration object 'z' by typing\n");
printf(".L fitZee.C+\n");
printf("fitZee z\n");

gSystem->Exec("rm -f ElecCalib_C.so");
gSystem->Exec("rm -f fitZee_C.so");
//gSystem->Exec("rm -f t16*.*");
//gSystem->Exec("rm -f t78*.*");
//gSystem->Exec("rm -f tf7*.*");

//gInterpreter->LoadMacro("fitZee.C+");
//fitZee z;
//printf("Created a new calibration object 'z'\n");
//printf("\n Please try the commands z.Fit(\"\") and z.List()\n");

 gStyle->SetStatW(0.2);
 gStyle->SetStatH(0.2);
//gStyle->SetMarkerColor(4);
//gStyle->SetMarkerStyle(20);
//gStyle->SetStatFontSize(0.3);
//gStyle->SetOptStat(0111100);

// print overflows/underflows in the stat box
gStyle->SetOptStat(11);
// print fit results in the stat box
gStyle->SetOptFit(1110);
// set minimum of histogram to zero
gStyle->SetHistMinimumZero(true);
gStyle->SetPalette(1); 

}
