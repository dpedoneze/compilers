var YN : text;

begin
 writeln('Y(YES) or N(NO)?');
 repeat {repeat the code for at least one time}
  YN := 'YES';
  if YN = 'YES' then writeln('YES');
  if YN = 'NO' then writeln('Why not? Exiting...');
 until (YN = 'YES');
end.