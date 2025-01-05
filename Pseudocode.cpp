/*PSEUDOCODE*/
//declare va_list variable
//use va_start(<va_list varibale>, <last fixed argument (in this case - const char *)>)
//parse the string and use write:
//__while string[index] is not '\0'
//____if string[index] is not '%' => write(1, &string[index], 1);
//____else =>
//______if string[index + 1] is '%' => print out '%', increment index
//______else =>
//________save specifier with flags:
//__________declare a const char pointer, create a new index, count length of specifer (while string[index2] is not alpha and not '\0' => counter++; index2++; if string[index2] is alpha => counter++) *if no alpha encountered until the end, then it should be just printed out
//__________malloc space for flag and assign relevant chars to it
//________another function (takes index address to modify it, last char of flag string as specifier, and the whole flag string)
//another function:
//__if specifier is 's' => 
//____declare const char variable and assign va_arg(<va_list varibale>, const char *) to it
//____write(1, <const char * variable>, ft_strlen(<const char * variable>));
//__if specifier is 'c' => 
//____declare char variable and assign va_arg(<va_list varibale>, int!!!) to it
//____write(1, &<char variable>, 1);
//__if specifier is 'd' or 'i' => putnbr
//__if specifier is 'u' => 
//____declare unsigned int variable and assign va_arg(<va_list varibale>, unsigned int) to it
//____putnbr
//__if specifier is 'x' or 'X' =>
//____function transforming decimal to hexadecimal
//____function transforming hexadecimal to text
//____write
//__if specifier is 'p' =>
//____declare void * variable and assign va_arg(<va_list varibale>, void *) to it
//____function transforming hexadecimal to text
//____write
//__else => print the whole flag string (as it is non-valid specifier)