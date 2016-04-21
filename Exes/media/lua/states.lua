------------------------------------------------
------------------------------------------------
------------------------------------------------

Crawler_Patrol = {
	component = "CPatrol"
}

Crawler_Patrol["Enter"] = function(agent)

	print ("[Lua]: Enter State Patrol")
	agent: Activate(Crawler_Patrol.component)

end

Crawler_Patrol["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_name") == "Player_Body") then
		agent: ChangeState(Crawler_Attack)
	end

	if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_name") == "Player_Body") then
		agent: ChangeState(Crawler_Chase)
	end

end

Crawler_Patrol["Exit"] = function(agent)

	print ("[Lua]: Exit State Patrol")
	agent: Deactivate(Crawler_Patrol.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Crawler_Chase = {
	component = "CChase"
}

Crawler_Chase["Enter"] = function(agent)

	print ("[Lua]: Enter State Chase")
	agent: Activate(Crawler_Chase.component)

end

Crawler_Chase["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_name") == "Player_Body") then
		agent: ChangeState(Crawler_Attack)
	end

	if not agent: GetBoolValue("seeing_entity") or (agent: GetBoolValue("seeing_entity") and not agent: GetStringValue("seen_entity_name") == "Player_Body")then
		agent: ChangeState(Crawler_Alert)
	end

end

Crawler_Chase["Exit"] = function(agent)

	print ("[Lua]: Exit State Chase")
	agent: Deactivate(Crawler_Chase.component)

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Crawler_Alert = {
	component = "CAlert",
	wait_time = 5000,
	accum_time = 0
}

Crawler_Alert["Enter"] = function(agent)

	print ("[Lua]: Enter State Alert")
	Crawler_Alert.accum_time = 0

end

Crawler_Alert["Execute"] = function(agent, msecs)

	if agent: GetBoolValue("touching_entity") and (agent: GetStringValue("touched_entity_name") == "Player_Body") then
		agent: ChangeState(Crawler_Attack)
	end

	if agent: GetBoolValue("seeing_entity") and (agent: GetStringValue("seen_entity_name") == "Player_Body") then
		agent: ChangeState(Crawler_Chase)
	end

	Crawler_Alert.accum_time =  Crawler_Alert.accum_time + msecs

	if Crawler_Alert.accum_time >= Crawler_Alert.wait_time then
		Crawler_Alert.accum_time = 0
		agent: ChangeState(Crawler_Patrol)
	end

end

Crawler_Alert["Exit"] = function(agent)

	print ("[Lua]: Exit State Alert")

end

------------------------------------------------
------------------------------------------------
------------------------------------------------

Crawler_Attack = {
	component = "CAttack"
}

Crawler_Attack["Enter"] = function(agent)

	print ("[Lua]: Enter State Attack")
	agent: Activate(Crawler_Attack.component)

end

Crawler_Attack["Execute"] = function(agent, msecs)

	--print ("[Lua]: Executing State Attack")

end

Crawler_Attack["Exit"] = function(agent)

	print ("[Lua]: Exit State Attack")
	agent: Deactivate(Crawler_Attack.component)

end
