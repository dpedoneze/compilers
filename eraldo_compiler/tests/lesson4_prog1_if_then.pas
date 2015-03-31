program lesson4_Program1;

var N1,N2, Total : real;
    Sel : char;  {this is a character variable type, 
                 which holds single characters ONLY}

begin
 Total := 0;  {always initialise integer/real variables}
 N1 := 1;
 N2 := 2;
 
 writeln('1.Addition');
 writeln('2.Subtraction');
 writeln('3.Exit');
 write('Select: ');
 Sel := '1';
 writeln(' 1 ');

 if Sel = '1' {action} then 
  begin  {more than one statement}
   write('Input No.1:'); 
   readln(N1);           
   writeln(' 1 ');
   write('Input No.2:'); 
   readln(N2);  
   writeln(' 2 ');         
   Total := N1 + N2;    
   writeln('Addition: N1,N2 = Total'); 
  end;  {Closing the if statement(begin)}
end.