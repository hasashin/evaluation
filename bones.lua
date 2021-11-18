--io.write("Bones.\n")

mapsize = 800;
--destination = Vector4d(mapsize/2,mapsize/2,0,0)
center = Vector4d(mapsize/2,mapsize/2,0,0)

function whatTo(agent, actorKnowledge, gametime)
	--io.write("Flesh entering - What to do?\n")
	if (actorKnowledge:getDirection():value(0) == 0)
	and	(actorKnowledge:getDirection():value(1) == 0)
	then
		--io.write(".")
		destination = Vector4d( agent:randomDouble() * mapsize, agent:randomDouble() * mapsize, 0, 0)
		io.write(".\n")
		agent:moveTo(destination)
		--io.write(".")
		
		--io.write("a")
		if (actorKnowledge:getAmmo(Enumerations.Chaingun) == 0)
		and (actorKnowledge:getAmmo(Enumerations.Railgun) == 0)
		and (actorKnowledge:getAmmo(Enumerations.RocketLuncher) == 0)
		and (actorKnowledge:getAmmo(Enumerations.Shotgun) == 0)
		then
			destination = Vector4d( agent:randomDouble() * mapsize, agent:randomDouble() * mapsize, 0, 0)
			io.write("..\n")
			agent:moveTo(destination)
		end
		if (actorKnowledge:getHealth() < 25)
		then
			destination = Vector4d( agent:randomDouble() * mapsize, agent:randomDouble() * mapsize, 0, 0)
			io.write("...\n")
			agent:moveTo(destination)
		end
	end
	
		foes = actorKnowledge:getSeenFoes()
		if (foes:size() > 0) then
			--io.write("1")
			dist = 999999
			for i = 0, foes:size()-1, 1 do 
				--io.write(".")
				dir = foes:at(i):getPosition() - actorKnowledge:getPosition()
				if dir:length() < dist then
					dist = dir:length()
					closest = foes:at(i)
				end
			end
			--///////////zmiany broni od dystansu i strzelanie
			if (dist < 70) then
				--io.write("2")
				agent:shootAt(closest)
				return
			end
			--///////////
		end

	--io.write("z")
	--io.write("\nFlesh exiting - What to do?\n")
end;