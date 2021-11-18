
counter = 0
function dumb7whatTo( agent, actorKnowledge, time)

  enemies = actorKnowledge:getSeenFoes()
  if ( enemies:size() > 0) then
     dir = enemies:at(0):getPosition() - actorKnowledge:getPosition()
     agent:moveDirection( dir*(-1))
     if ( dir:length() < 20) then
	 dest = Vector4d( agent:randomDouble()*800, agent:randomDouble()*800, 0,0)
         agent:moveTo( dest )
     end
  	     
     io.write( "He's holding ", enemies:at(0):getWeaponType())
     io.write( " distance: ", dir:length(), "\n")
  end
  
  
end;

function dumb7onStart( agent, actorKnowledge, time)
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