program lesson4;

var score : integer;

begin

writeln('Who has discovered the land of America?');
readln(ans);

if (ans = 'Christopher Colombus') then 
 score := score + 1                                      {if this is false,}
else
 writeln('sorry, you have got it wrong!');             {then this is true}
end.