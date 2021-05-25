#include "process_data.h"


void process_command(unsigned long *command, unsigned int command_size)
{

    unsigned char command_code_size = *command >> (command_size - 2); 
    unsigned char command_code=0;
    switch (command_code_size)
    {
    case 0:
        /* 00 */
        command_code = QUERY_REP_COMMAND;
        return 
        break;
    case 1:
        /* 01 */
        command_code = ;
        
        break;
    case 2:
        /* 10 */
        command_code = *command >> (command_size - 4);

        break;
    case 3:
        /* 11 */
        command_code = *command >> (command_size - 8);

        break;
    
    default:
        break;
    }
    

}