
counter = 0
function dumb8whatTo( agent, actorKnowledge, time)
  
  nav = actorKnowledge:getNavigation()
  
  for i=0, nav:getNumberOfTriggers() -1, 1 do
     trig = nav:getTrigger( i)
     if ( trig:getType() == Trigger.Health and
          trig:isActive() == false) then
	agent:moveTo( trig:getPosition())
     end
     
  end  
  
end;

function dumb8onStart( agent, actorKnowledge, time)
  io.write("dumb8 started\n")
end


function log( name, msg)
    io.write( name )
    io.write( ": ")
    io.write( msg)
    io.write( "\n")
end;

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