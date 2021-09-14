#include <stdint.h>
#include <stdio.h>

#include "cliquest_error.h"
#include "data_table.h"
#include "scene.h"
#include "system.h"

/*
error_code_e cli_scene_xx(data_table_t *data_table){
  return RC_SUCESS;
}
*/

void cli_scene_game_start(data_table_t *data_table) {
  char input_data[ANY_INPUT_MAX];
  CLI_PRINT(" ");
  CLI_PRINT(" ");
  CLI_PRINT(
      "            ..Jggg+.,          ...                   ...                        ..(ggg&-,.           ....       "
      "        ...      ...................        ..Jggg+..       .......................");
  CLI_PRINT(
      "         .dMMM^^^^^MMMN,       (MN                   -MM                     .&MMMY^^^^HMMNJ         .MM~       "
      "        dM@      -MMMMMMMMMMMMMMMMM@     .MMMM^^^^WMMMa.    .MMMMMMMMMMMMMMMMMMMMME");
  CLI_PRINT(
      "       .MM#^         ?MMN.     (MN                   -MM                   .dMM^          TMN,       .MM_       "
      "        dM@      -MM                    dMM^         TMMx             -MM");
  CLI_PRINT(
      "      .MMt             UMN.    (MN                   -MM                  .MMF             .MMp      .MM_       "
      "        dM@      -MM                   -MM            ,MMp            -MM");
  CLI_PRINT(
      "     .MM|               WMF    (MN                   -MM                 .MMF               .MM]     .MM_       "
      "        dM@      -MM                   dM#             ,!             -MM");
  CLI_PRINT(
      "    .MMF                       (MN                   -MM                 gM#                 JMN.    .MM_       "
      "        dM@      -MM                   (MM,                           -MM");
  CLI_PRINT(
      "    .MM!                       (MN                   -MM                .MM]                 .MM]    .MM_       "
      "        dMF      -MM                    TMMa.                         -MM");
  CLI_PRINT(
      "    JMM                        (MN                   -MM                .MM}                  MMF    .MM_       "
      "        dMF      -MMNNNNNNNNNNNm         .TMMMNN&...                  -MM");
  CLI_PRINT(
      "    dMN                        (MN                   -MM                ,MM{                  MMF    .MM_       "
      "        dMF      -MM^^^^^^^^^^^^             ?^^MMMMMN&.              -MM");
  CLI_PRINT(
      "    JMM                        (MN                   -MM                ,MM)                  MMF    .MM_       "
      "        dMF      -MM                                ?YMMN,            -MM");
  CLI_PRINT(
      "    ,MM;                       (MN                   -MM                 MMb                 .MM|    .MM_       "
      "        dMF      -MM                                   UMM,           -MM");
  CLI_PRINT(
      "     MMN                .,.    (MN                   -MM                 -MN.                dM#     .MM_       "
      "        dMF      -MM                                    MM]           -MM");
  CLI_PRINT(
      "     .MMb               dM@    (MN                   -MM                  ?MN.              .MM'      MM]       "
      "       .MM$      -MM                  dMN.              MMF           -MM ");
  CLI_PRINT(
      "      ,MMN,           .dM@     (MN                   -MM                   /MN,           .JMM^       -MN,      "
      "      .MMF       -MM                   MMN.            .MM'           -MM");
  CLI_PRINT(
      "        TMMN,.      .+MMD      (MN                   -MM                    .WMN,.      .JMMD          ,MMa,.   "
      "    .JMMD        -MM                    TMMa.       ..MMM^            -MM");
  CLI_PRINT(
      "          7HMMMMMMMMM#^        (MMMMMMMMMMMMMMMMM[   -MM                      (YMMMMMMMMMM^              "
      "?YMMMMMMMMMM#^          -MMMMMMMMMMMMMMMMMM      TMMMMMMMMMMMB^              -MM");
  CLI_PRINT(
      "               $$!                                                                _?UMN.                      "
      "~$$!                                             $$?! ");
  CLI_PRINT("                                                                                     MMh.");
  CLI_PRINT("                                                                                      TMMMMMMMM ");
  CLI_PRINT("                                                                                         _?!! ");
  CLI_PRINT(" ");
  CLI_PRINT(" ");
  CLI_PRINT(
      "                                                     M^^^9a,  J#^^^W,  .M^^^^^  .J^^Ya   .V^^9x       d^^^^^$  "
      "Mh    J[ (^^YM^^^  J#^^^^5  M^^^YQ,");
  CLI_PRINT(
      "                                                     H    .#  J)    d: .@       M.   ,^  M    (!      d~       "
      "#,h.  J[    .#     J)       M     N");
  CLI_PRINT(
      "                                                     M....Jt  Ja...JD  .N+++J   ,9a..    (8a.,        da+++.   "
      "# ,N. J[    .#     Jm+++,   M....d=");
  CLI_PRINT(
      "                                                     H        J)  ?p   .@            Tb      .Up      d~       "
      "#  .N.J[    .#     J)       M   4,");
  CLI_PRINT(
      "                                                     H        J)   ?p  .@      .N.   .F .h.   .F      d~       "
      "#   .N([    .#     J)       M    W,");
  CLI_PRINT(
      "                                                     ^        ?'    7' .^^^^^^!  7^^^=    ^^^^^       7^^^^^^  "
      "^     ^^    .^     ?^^^^^^  ^     ^");
  cli_get_input_data(input_data, sizeof(char) * ANY_INPUT_MAX, DATA_TYPE_CHAR);
  CLI_PRINT(" ");
  data_table->next_scene = MAIN_MENU;
}

void cli_scene_maou_castle(data_table_t *data_table) {}