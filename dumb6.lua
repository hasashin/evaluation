
counter = 0
function dumb6whatTo( agent, actorKnowledge, time)
  enemies = actorKnowledge:getSeenFoes()
  if ( enemies:size() > 0) then
     dir = enemies:at(0):getPosition() - actorKnowledge:getPosition()
     agent:rotate( dir)
     io.write( "He's holding: ", enemies:at(0):getWeaponType(), "\n")
     io.write( " distance: ", dir:length(), "\n")
  end
  
end;

function dumb6onStart( agent, actorKnowledge, time)
--  io.write("My name is: ", actorKnowledge:getName(), "\n");
--  io.write("counter: ")
--  io.write( counter)
--  io.write( "\n")
--  counter = counter + 1
end

function showVector( vector)
    io.write( "(")
    io.write( vector:value(0))
    io.write( ",")
    io.write( vector:value(1))
    io.write( ",")
    io.write( vector:value(2))
    io.write( ",")
    io.write( vector:value(3))
    io.write( ");")
end;