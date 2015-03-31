program nested;

var Sel, YN : char;

begin

if Sel = '3' then 
 begin
   write('Are you sure?(Y/N)');
   YN := 'y';
   if YN = 'y'  then write(' y ');  {Nested if statement}
   if YN = 'n' then  write(' n ');{Another Nested if statement} 
 end;
end.