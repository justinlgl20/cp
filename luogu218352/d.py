kills = []
players=[]
fail=0
turn=0;
class villager:
	alive=1;
	immortal=0;
	dead=0;
	def __init__(self, i){
		self.i=i;
	}
	def night(self):
		if(self.immortal):
			fail=1;
		self.immortal=0
	def die(self):
		if(self.immortal==0 and self.alive):
			self.alive=0;
			kills.append(i)
			dead=turn;
		if(self.immortal):
			self.immortal=0;
class wolf(villager):
	def kill(self, j):
		players[j].die();
class witch(villager):
	potion=0
	poison=0
	def kill(self, j):
		if(poison>0):
			fail=1
		poison=turn;
		players[j].die();
	def save(self, j):
		if(potion>0):
			fail=1
		potion=turn;
		players[j].immortal=1;
		if(players[j].alive==0):
			fail=1
		
	def night(self):
		self.immortal=0
		if(poison==potion and potion!=0):
			fail=1;
class hunter(villager):
	def die(self):
		if(self.immortal==0 and self.alive):
			self.alive=0;
			kills.append(i)
			dead=turn;
	def takedown(self, j):
		if(self.alive==1 or dead!=turn):
			players[j].die();
