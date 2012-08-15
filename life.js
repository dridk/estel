
function step()
{
    life.age ++;

    if (life.age == 5)
        life.replicate(life.x+1, life.y+1);

    
    
        return true;
}
