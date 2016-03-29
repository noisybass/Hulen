State_Prueba = {}

State_Prueba["Enter"] = function(CFSMEntity)

	print ("[Lua]: Enter")

end

State_Prueba["Execute"] = function(CFSMEntity)

	CFSMEntity: SayHello()

end

State_Prueba["Exit"] = function(CFSMEntity)

	print ("[Lua]: Exit")

end

State_Prueba["Probando"] = function()
	
	print ("ASGFAGAGAGAGAG")

end

State_Prueba["ProbandoConArgumentos"] = function(CFSMEntity)

	CFSMEntity: SayHello()

end