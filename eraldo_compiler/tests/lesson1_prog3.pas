program Lesson1_Program3;

var       
    Num1, Num2, Sum : integer;

begin {no semicolon}
 write('Input number 1:'); 
 readln(Num1);
 writeln('Input number 2:');
 readln(Num2);
 Sum := Num1 + Num2; {addition} 
 writeln(Sum);
 readln;
end.