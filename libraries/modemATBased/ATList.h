#ifndef ModemATList_h
#define ModemATList_h

const String modem_ip_single					 =  "AT+CIPMUX=0\r";//OK
//const String modem_ip_multi						 =  "AT+CIPMUX=1\r";//OK
const String modem_ip_mode_normal				 =  "AT+CIPMODE=0\r";//OK-ERROR
//const String modem_ip_mode_transparent			 =  "AT+CIPMODE=1\r";//OK-ERROR
const String modem_internet_connect				 =  "AT+CGDCONT=1,\"IP\",\"TATA.DOCOMO.INTERNET\",\"10.6.6.6\",0,0\r";//OK-ERROR
const String modem_interner_connect_password	 =  "AT+CSTT=\"TATA.DOCOMO.INTERNET\"\r";//OK_ERROR
const String modem_deactive_gprs_dpd			 =  "AT+CIPSHUT\r";//OK-CLOSE OK-ERROR
const String modem_deactive_gprs_dpd_ok			 =  "SHUT OK\r\n";//OK-CLOSE OK-ERROR

const String modem_connect_host_and_port_1of3	 =  "AT+CIPSTART=\"TCP\",\"";//OK-+CME ERRORn-ALREADY CONNECT-STATE:n-CONNECT FAIL-CONNECT OK
const String modem_connect_host_and_port_2of3	 =  "\",\"";
const String modem_connect_host_and_port_3of3	 =  "\"\r";
const String modem_connect_host_and_port_ok      =  "CONNECT OK\r\n";

const String modem_start_send_data_over_tcp_udp	 =  "AT+CIPSEND\r";

const String modem_header_get_send_1of3			 =  "GET ";
const String modem_header_get_send_2of3          =  "q";
const String modem_header_get_send_3of3			 =  " HTTP/1.1\r\n";
const String modem_header_host					 =  "Host: ";
const String modem_header_hostString             =  "h";
const String modem_header_hostPort				 =  "p";
const String modem_heafer_connection_alive		 =  "Connection: Keep-Alive\r\n";
const String modem_header_accept				 =  "Accept: */*\r\n";
const String modem_header_connection_close		 =  "Connection: close\r\n\r\n";
const String modem_header_connection_close_ok	 =  "SEND OK\r\n";

const String modem_at_command_general_end_line   =  "\r\n";


//const String modem_sms_read_all					 =  "CMGL=\"ALL\"";
//const String modem_sms_delete_by_id				 =  "CMGD=";
//const String modem_sms_read_by_id				 =  "CMGR=";
//const String modem_sms_new_message				 =  "CNMI:";
//const String modem_modem_status					 =  "CPAS";//0 call ready - 2 unknow - 3 tocando - 4 em ligacao
//const String modem_modem_ring					 =  "RING";
//const String modem_modem_no_carrier				 =  "NO CARRIER";
const String modem_modem_ok						 =  "OK\r\n";
const String modem_modem_error					 =  "ERROR\r\n";

const String modem_sms_text_redy_to_send		 =  "> ";

// Comandos de 'echo' on/off faz o modem repetir tudo o que é enviado. 
// Deve ser a primeira coisa envoada ao modem
const String modem_echo_off						 =  "ATE0\r";//OK
//const String modem_echo_on						 =  "ATE1\r";//OK

    #ifndef I_do_not_need_to_send_sms_in_my_program
    
        const String modem_sms_text_mode				 =  "AT+CMGF=1\r";//OK
        const String modem_sms_send_confg_1of2           =  "AT+CMGS=\"";
        const String modem_sms_send_telefon              =  "t";
        const String modem_sms_send_confg_2of2           =  "\"\r";
        const String modem_sms_send_message              =  "m";
        
    #endif
    
    const String modem_bye							 =  byte ( 0x1A );
    const String modem_bye_ok						 =  "SEND OK\r\n";
    //const String modem_sms_send_ok                   =  "";

#endif