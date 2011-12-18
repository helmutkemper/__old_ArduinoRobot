const unsigned char modem_at_plus[4]						 =  { 'A', 'T', '+', 0x00 };

const unsigned char modem_echo_off[5]						 =  { 'A', 'T', 'E', '0', 0x00 };//OK
const unsigned char modem_echo_on[5]						 =  { 'A', 'T', 'E', '1', 0x00 };//OK

const unsigned char modem_ip_single[9]						 =  { 'C', 'I', 'P', 'M', 'U', 'X', '=', '0', 0x00 };//OK
const unsigned char modem_ip_multi[9]						 =  { 'C', 'I', 'P', 'M', 'U', 'X', '=', '1', 0x00 };//OK
const unsigned char modem_ip_mode_normal[10]				 =  { 'C', 'I', 'P', 'M', 'O', 'D', 'E', '=', '0', 0x00 };//OK-ERROR
const unsigned char modem_ip_mode_transparent[10]			 =  { 'C', 'I', 'P', 'M', 'O', 'D', 'E', '=', '1', 0x00 };//OK-ERROR
const unsigned char modem_internet_connect[53]				 =  { 'C', 'G', 'D', 'C', 'O', 'N', 'T', '=', '1', ',', '"', 'I', 'P', '"', ',', '"', 'T', 'A', 'T', 'A', '.', 'D', 'O', 'C', 'O', 'M', 'O', '.', 'I', 'N', 'T', 'E', 'R', 'N', 'E', 'T', '"', ',', '"', '1', '0', '.', '6', '.', '6', '.', '6', '"', ',', '0', ',', '0', 0x00 };//OK-ERROR
const unsigned char modem_interner_connect_password[29]		 =  { 'C', 'S', 'T', 'T', '=', '"', 'T', 'A', 'T', 'A', '.', 'D', 'O', 'C', 'O', 'M', 'O', '.', 'I', 'N', 'T', 'E', 'R', 'N', 'E', 'T"', 0x00 };//OK_ERROR
const unsigned char modem_deactive_gprs_dpd[8]				 =  { 'C', 'I', 'P', 'S', 'H', 'U', 'T', 0x00 };//OK-CLOSE OK-ERROR


const unsigned char modem_connect_host_and_port_1of3[17]	 =  { 'C', 'I', 'P', 'S', 'T', 'A', 'R', 'T', '=', '"', 'T', 'C', 'P', '"', ',', '"', 0x00 };//OK-+CME ERRORn-ALREADY CONNECT-STATE:n-CONNECT FAIL-CONNECT OK
const unsigned char modem_connect_host_and_port_2of3[4]		 =  { '"', ',', '"', 0x00 };
const unsigned char modem_connect_host_and_port_3of3[2]		 =  { '"', 0x00 };


const unsigned char modem_start_send_data_over_tcp_udp[8]	 =  { 'C', 'I', 'P', 'S', 'E', 'N', 'D', 0x00 };

const unsigned char modem_header_get_send_1of2[5]			 =  { 'G', 'E', 'T', ' ', 0x00 };
const unsigned char modem_header_get_send_2of2[10]			 =  { ' ', 'H', 'T', 'T', 'P', '/', '1', '.', '1', 0x00 };
const unsigned char modem_header_host[7]					 =  { 'H', 'o', 's', 't', ':', ' ', 0x00 };
const unsigned char modem_heafer_connection_alive[23]		 =  { 'C', 'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', ':', ' ', 'K', 'e', 'e', 'p', '-', 'A', 'l', 'i', 'v', 'e', 0x00 };
const unsigned char modem_header_accept[12]					 =  { 'A', 'c', 'c', 'e', 'p', 't', ':', ' ', '*', '/', '*', 0x00 };
const unsigned char modem_header_connection_close[18]		 =  { 'C', 'o', 'n', 'n', 'e', 'c', 't', 'i', 'o', 'n', ':', ' ', 'c', 'l', 'o', 's', 'e', 0x00 };
const unsigned char modem_bye[2]							 =  { 26, 0x00 };




const unsigned char modem_sms_text_mode[7]					 =  { 'C', 'M', 'G', 'F', '=', '1', 0x00 };//OK
const unsigned char modem_sms_read_all[11]					 =  { 'C', 'M', 'G', 'L', '=', '"', 'A', 'L', 'L', '"', 0x00 };
const unsigned char modem_sms_delete_by_id[6]				 =  { 'C', 'M', 'G', 'D', '=', 0x00 };
const unsigned char modem_sms_read_by_id[6]					 =  { 'C', 'M', 'G', 'R', '=', 0x00 };
//const unsigned char modem_sms_send_1of2[7]					 =  { 'C', 'M', 'G', 'S', '=', '"', 0x00 };
//const unsigned char modem_sms_send_2of2[2]					 =  { '"', 0x00 };
const unsigned char modem_sms_new_message[6]				 =  { 'C', 'N', 'M', 'I', ':', 0x00 };
const unsigned char modem_modem_status[5]					 =  { 'C', 'P', 'A', 'S', 0x00 };//0 call ready - 2 unknow - 3 tocando - 4 em ligacao
const unsigned char modem_modem_ring[5]						 =  { 'R', 'I', 'N', 'G', 0x00 };
const unsigned char modem_modem_no_carrier[11]				 =  { 'N', 'O', ' ', 'C', 'A', 'R', 'R', 'I', 'E', 'R', 0x00 };
//const unsigned char modem_modem_ok[7]						 =  { '\r', '\n', 'O', 'K', '\r', '\n', 0x00 };
const unsigned char modem_modem_ok[5]						 =  { 'O', 'K', '\r', '\n', 0x00 };
const unsigned char modem_modem_error[6]					 =  { 'E', 'R', 'R', 'O', 'R', 0x00 };

const unsigned char modem_sms_send_confg[9]                        =  { 'C', 'M', 'G', 'S', '=', '"', 0x80, '"', 0x00 };
const unsigned char modem_sms_text_redy_to_send[2]			 =  { '>', 0x00 };

/*
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
const unsigned char modem_[]				 =  { '', 0x00 };
*/