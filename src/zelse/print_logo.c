#include <stdio.h>


// 颜色重置
#define RESET   "\033[0m"

// 前景色
#define BLACK   "\033[30m"   // 黑色
#define RED     "\033[31m"   // 红色
#define GREEN   "\033[32m"   // 绿色
#define YELLOW  "\033[33m"   // 黄色
#define BLUE    "\033[34m"   // 蓝色
#define MAGENTA "\033[35m"   // 洋红色
#define CYAN    "\033[36m"   // 青色
#define WHITE   "\033[37m"   // 白色

// 背景色
#define BG_BLACK   "\033[40m"   // 黑色背景
#define BG_RED     "\033[41m"   // 红色背景
#define BG_GREEN   "\033[42m"   // 绿色背景
#define BG_YELLOW  "\033[43m"   // 黄色背景
#define BG_BLUE    "\033[44m"   // 蓝色背景
#define BG_MAGENTA "\033[45m"   // 洋红色背景
#define BG_CYAN    "\033[46m"   // 青色背景
#define BG_WHITE   "\033[47m"   // 白色背景

#define BOLD "\033[1m"

int main()
{

    printf(BOLD BLUE"\r\n"RESET);
    printf(BOLD BLUE" /\\_/\\"RESET"\r\n");
    printf(BOLD BLUE"( o.o )"RESET"\r\n");
    printf(BOLD BLUE" > ^ <"RESET"\r\n");
    printf(BOLD BLUE"/     \\"RESET"\r\n");
    printf(YELLOW"CIAO-OS"RESET"\r\n");
    printf(YELLOW" v1.03"RESET"\r\n");
    // printf(" _____\n");
    
// printf("
// printf("                                                                  
// printf("                                                      i?>`                                            "_)//)?i"                                       
// printf("                                                    _mB$$MY<                                        'nW$$$$$$@Mwx<                                    
// printf("                                                  'v@$$#Xq$@U:                                      "W$$$$$$$$$$$@w]                                  
// printf("                                                 ,m$$$0,  1&$o~                                      >cZkM@$$$$$$$$$J^                                
// printf("                                                Ib$$$Z`    >M$W+                                        .^i(Q%$$$$$$$Z`                               
// printf("                                          ,<{jXQ#$$$$#bpZCc\Q$$#I                                            >p$$$$$$$n                               
// printf("                                     .!|Ub&$$$$$$$$$$$$$$$$$$$$$m^                                            :#$$$$$$#"                              
// printf("                           .`":;l!!~xbB$$$$$$$$$$$$$$$$$$$$$$$$$$ac[;            ',i?)jcUQOmmmZ0CYn\[>,.       X$$$$$$B!                              
// printf("                      `]xCqa#&%BBB@$$$$$$$$$$$$$$$$$$$$$8&@$$$$$$8B$8pf;   `l?/Ywo&@$$$$$$$$$$$$$$$$$@WbU)l    n$$$$$$&:                              
// printf("                      )$$$B*aaaa$$$$$$$$$$$$$$$$$$$$$$o]"^!x@$#Luzh$$$$WzcZoB$$$$$$$$$$$$$$$$$$$$$$$$$$$$$%w(^ O$$$$$$Y                               
// printf("                      l#$$n ..'u@$$$$$$$$$$$$$$$$$$$$$Q:+(uQwj|cZwOLQ&$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ozB$$$$$C`                               
// printf("                       ip$8|. }$$$$$$$$$$$$$$$$$$$$$@$$@$$$x'"{/xcCZkB$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*\.                                
// printf("                        '/#$k)0$$$$$$$B0f\nm%$$$$m/<x@#m$$$kddbkbpqmm%$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$X^                                  
// printf("                          "ta$$$$$$$$$m   !\o$$@*Oj.}jf0$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$h]                                  
// printf("                            '-YW$$$$$$Brcp#WM@$BYzuZ@@$$$$$$$$$$8qxfW$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$w/>^                              
// printf("                               Z$$$8kQUUz/?`+M$$$$$$$$$$$$$$@hY}!~jb@$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$@#pJx)>.                        
// printf("                              )$$$BJQbmcxn+/W$$$$$$$$$$$$8Z\>I?ck@$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$@k/'                      
// printf("                             .b$$$$$krudp}O$$$$$$$$$$$$af;;)0W$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$0`                     
// printf("     !+~++~~~~~~~~~++++++~~+; n$$$$$Zo$W-k$$$$$$$$$$$8j`lJ8$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$8: >+++++++++++++<.    
// printf("     l~<<~~~~~~~~~~~~~~~~~~~:  ]Jk#8@@@&oB8W#okq0Uvf)i >%$$$$$$$$$$@a0zxrrxxnnuvvccczzXYYYYYYYJCQOmppdkkkkbpm0QOd&$$$$$$$$$WdZc>  >+++++++++++++<.    
// printf("                                  ^:l!ii!I:"^'.        <&$$$$$$$MZt>'                                  ...       :|w%$$$$$B?                          
// printf("                                                        I\cUYn|+"                                                   l)vCLu<                           
// printf("                                                                                                                                                      
// printf("                                                                                                                                                      
// printf("                                                                                                                                                      
// printf("         l{nCmpdpmCx}I       |ccc/           `nzzzz[              ^+\zQwpppZJn{l                         :?fY0qppq0Yj];          "-fYOqppqZCc/?l`     
// printf("      '(pB$$$$%8%$$$$8Z].    p$$$k          'Q$$$$$B}           >Y#$$$$$%%B$$$$Bp|'                    [O&$$$$@%%@$$$$8Z}.     "cM$$$$%88%@$$$$$Y.    
// printf("     ;m$$$%U[!,",l]U%$$M|    w$$$p          Y$$$%$$$8-         xB$$$kx-l:,;>)QB$$$dl                 :0$$$@O(<;,,;~|m$$$$O:   .Q$$$W{I""",I>]fCd>     
// printf("    `p$$$*<         i+l"`    q$$$d         n$$$&+v$$$W+       t$$$$u'         _M$$$k"               'm$$$&]          {8$$$q'  .p$$$W|!^               
// printf("    [$$$$1                   q$$$d        /$$$@} .0$$$#!     ^*$$$p            ($$$$1               +$$$$j            v$$$$-   !ZB$$$$&aqQXj1~,       
// printf("    \$$$$+                   w$$$d       1@$$@\   'q$$$aI    :8$$$Q            ~$$$$/  Ipbbbbbbbb}  [$$$${            \$$$${     !(XmaW@$$$$$$&m1.    
// printf("    >@$$$U          ';`      Z$$$d      -%$$$%Q000Qb$$$$b"   .Z$$$&<           C$$$B>  Iqddpppppd[  :&$$$m'          ^p$$$&;         ."I>?(vp@$$$j    
// printf("     r$$$$C>.     .+w8#hn.   O$$$d     >W$$$&W88888&MB$$$m^   la$$$W\,      .~Q$$$$t                 )B$$$w-'      `]p$$$%)    ju?;'        :#$$$O    
// printf("      )a$$$@kCcuzQh$$$@Ql    Z$$$d    Io$$$O:""""""""?%$$$L.   :Y8$$$&wUcvzQh$$$$b[                   +w@$$$o0XvvYZ#$$$@Z~    [$$$B*pQYzccYOM$$$M-    
// printf("       `}Uk8$$$$$$$Wqn>      0BBBq   ^m@BBb,          )8BB@n.    l/Qa%$$$$$$$Wdc-.                      ~nw#@$$$$$$B*Zr>      ;{u0h&@$$$$$$$B#mj:     
// printf("          .:>_?]?+!"         :lll;   `!lll^            Illll.       ':>+???+!"                             ^I>-??->I`             ."I>~-??_>I^        
// printf("                                                                                                                                                      
// );




// printf("\r\n");                                                                                                                        
// printf("                                          lrJn+.                                 +v0wmQc(>'\r\n");                             
// printf("                                        'r8$Ba@b[                               >$$$$$$$$@hx:\r\n");                           
// printf("                                       ,O$$ml -*$z'                             `/0d#B$$$$$$M)\r\n");                          
// printf("                                    .\">b$$#_;,'Ih$J.                                `!|p$$$$$@(\r\n");                         
// printf("                               \"~|zZkMB$$$@B%%&#do$$x                                   .u$$$$$W:\r\n");                        
// printf("                       .`^\"\"I|0M$$$$$$$$$$$$$$$$$$$@X-,          ."l~])/jrrjt|{_!"      `*$$$$$]\r\n");                        
// printf("                 .+rJph*WWWW%%$$$$$$$$$$$$$$$%oM@$$$BMB&m/, ';_|cZkMB$$$$$$$$$$$$BMbU)l   b$$$$$+\r\n");                        
// printf("                 'a$$OYYXk$$$$$$$$$$$$$$$$$bI';t%aJX0#8$$#mh8$$$$$$$$$$$$$$$$$$$$$$$$%%Z[!&$$$$0'\r\n");                        
// printf("                  ]W$f  <W$$$$$$$$$$$$$$$$$#YwoO?-jzJJ0W$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$W$$$BX^\r\n");                         
// printf("                   lC@p]O$$$$$$kYYw8$$$oz\\#&*$$wcJOOZZZW$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$q>\r\n");                           
// printf("                     <JW$$$$$$&I.ita$$oL{!ccp$$$$$$$$$@$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$a}'\r\n");                          
// printf("                       :)&$$$BWUUOLU8$omq8$$$$$$$$#Qf)p$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$kX)<:'\r\n");                     
// printf("                        ?B$BOCQYn|luB$$$$$$$$$%qx[]tO&$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$8oZ/"\r\n");                  
// printf("                       .b$$$&ZzOCta$$$$$$$$$h/~]zk@$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$o<\r\n");                 
// printf("    <?---------------?~.xB$$$k$8xB$$$$$$$BMt,fo$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$@) ~??????????_.\r\n");   
// printf("    \",,,,,,,,,,,,,,,,,\"  !|vJ00QLCXvx/)]+!\" ($$$$$$$Bkz)_<<<<~~++++__-???-?][{)|\\/jjf/|1{(vk$$$$$$o/)!  \":,::::::::,.\r\n");   
// printf("                                            :vqhkmY(!.                                     '+umaa0>\r\n");                     
// printf("                                               ..                                              .'\r\n");                       
// printf("\r\n");                                                                                                                        
// printf("        \"i?)({_l'      ,!ll.         !!!!.            ^!_{)([>,                      ^!-{(|]>,          'l+1()}+l"\r\n");      
// printf("     \"\mW$$$$$$$*L]'   YBBM;        c@@@@Y.        \"\ZM$$$$$$$8prI                ,/ZW$$$$$$$8dn!     ~Jo@$$$$$$$8hn.\r\n");   
// printf("    +a$$#x-!li]z&Bo|   U$$&;       x$$B%$$c       ?*$$#v]>li-rh$$&\              }#$$*n?>li-fk$$8j.  <B$$Z+I;I!_)um{\r\n");    
// printf("   :#$$p,       ::`'   U$$&;      /$$@{]B$$x     !&$$w,       `L$$@-            >B$$O"       'Y$$$)  >&$$ar[<I".\r\n");        
// printf("   }$$$(               U$$&;     )@$@/  (B$$f    /$$${         >@$$v  -((((((}. f$$$?         lB$$Q   !vd&$$$$BMdJ\;\r\n");    
// printf("   ~$$$Y        '^.    Y$$&;    ?%$$WxnnxM$$$(   ?$$$Y         t$$$(  Yoooooom` ]$$$u         |$$$x      ^l_{tv0#$$&]\r\n");   
// printf("   .n$$$J<`  ."]dWax.  z$$&;   ~W$$okaaaaka$$B}  .u$$$C+^   `iu@$$C'  ........  .X$$$Y<`   `iuB$$O"  <J\~,'    .1@$$c\r\n");   
// printf("     }wB$$Whka8$$#v:   Y$$BI  iW$$m^ .... `0$$@]   ]Z8$$&akhW$$Bp).               }m8$$WhkhW$$Bp(.   c8$$BWohkaW$$%Q;\r\n");   
// printf("       l{xYLQCc/+^     ]nnj^  }unr:        "jnn\'    :?tzJQLYx{l                    ;]fzJLCXj[l      .">}tvYJCJXr}l\r\n");     
// printf("\r\n");                                                                                                                        



// FILE *file = fopen("ascii_art.txt", "r");
// if (file != NULL) {
//     char line[256];
//     while (fgets(line, sizeof(line), file) != NULL) {
//         printf("%s", line);
//     }
//     fclose(file);
// }

// printf("   ____ ___    _    ___  \r\n");
// printf("  / ___|_ _|  / \\  / _ \\ \r\n");
// printf(" | |    | |  / _ \\| | | |\r\n");
// printf(" | |___ | | / ___ \\ |_| |\r\n");
// printf("  \\____|___/_/   \\_\\___/ \r\n");
// printf("                         \r\n");



    // printf("  /\\_./\\ \n");
    // printf(" ( o.o )  \n");
    // printf("  > ^ <  \n");
    // printf(" /       \\\n");

    // printf("  /\\_/\\\n");
    // printf(" ( o.o )______\n");
    // printf("  `--(  ______)\n");
    // printf("     /       \\\n");

    // printf("   /\\_/\\\n");
    // printf("  / o o \\\n");
    // printf(" (   \"   )\n");
    // printf("  \\~(*)~/\n");
    // printf("   \'-\'-\n");

    return 0;
}





