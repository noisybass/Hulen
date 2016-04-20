------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Patrol = {
	component = "CPatrol"
}

State_Patrol["Enter"] = function(agent)

	print ("[Lua]: Enter State Patrol")
	agent: Activate(State_Patrol.component)

end

State_Patrol["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_name") == "Player_Body") then
		agent: ChangeState(State_Attack)
	end

	if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_name") == "Player_Body") then
		agent: ChangeState(State_Chase)
	end

end

State_Patrol["Exit"] = function(agent)

	print ("[Lua]: Exit State Patrol")
	agent: Deactivate(State_Patrol.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Chase = {
	component = "CChase"
}

State_Chase["Enter"] = function(agent)

	print ("[Lua]: Enter State Chase")
	agent: Activate(State_Chase.component)

end

State_Chase["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_name") == "Player_Body") then
		agent: ChangeState(State_Attack)
	end

	if not agent: GetBoolValue("seeing_entity") or (agent: GetBoolValue("seeing_entity") and not agent: GetStringValue("seen_entity_name") == "Player_Body")then
		agent: ChangeState(State_Alert)
	end

end

State_Chase["Exit"] = function(agent)

	print ("[Lua]: Exit State Chase")
	agent: Deactivate(State_Chase.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Alert = {
	component = "CAlert",
	wait_time = 5000,
	accum_time = 0
}

State_Alert["Enter"] = function(agent)

	print ("[Lua]: Enter State Alert")
	State_Alert.accum_time = 0

end

State_Alert["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_name") == "Player_Body") then
		agent: ChangeState(State_Attack)
	end

	if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_name") == "Player_Body") then
		agent: ChangeState(State_Chase)
	end

	State_Alert.accum_time =  State_Alert.accum_time + msecs

	if State_Alert.accum_time >= State_Alert.wait_time then
		State_Alert.accum_time = 0
		agent: ChangeState(State_Patrol)
	end

end

State_Alert["Exit"] = function(agent)

	print ("[Lua]: Exit State Alert")

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

State_Attack = {
	component = "CAttack"
}

State_Attack["Enter"] = function(agent)

	print ("[Lua]: Enter State Attack")
	agent: Activate(State_Attack.component)

end

State_Attack["Execute"] = function(agent, msecs)

	--print ("[Lua]: Executing State Attack")

end

State_Attack["Exit"] = function(agent)

	print ("[Lua]: Exit State Attack")
	agent: Deactivate(State_Attack.component)

end
