------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Patrol = {}

State_Patrol["Component"] = "CPatrol"

State_Patrol["Enter"] = function(agent)

	print ("[Lua]: Enter State Patrol")

end

State_Patrol["Execute"] = function(agent)

	if agent: GetValues(): GetBoolValue("SeeingPlayer") then
		agent: ChangeState(State_Chase, State_Patrol["Component"], State_Patrol["Component"])
	end

end

State_Patrol["Exit"] = function(agent)

	print ("[Lua]: Exit State Patrol")

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Chase = {}

State_Chase["Component"] = "CChase"

State_Chase["Enter"] = function(agent)

	print ("[Lua]: Enter State Chase")

end

State_Chase["Execute"] = function(agent)

	if not agent: GetValues(): GetBoolValue("SeeingPlayer") then
		agent: GetFSM(): ChangeState(State_Patrol)
	end

end

State_Chase["Exit"] = function(agent)

	print ("[Lua]: Exit State Chase")

end
