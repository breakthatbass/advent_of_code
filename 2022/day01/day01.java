import java.io.*;
import java.util.*;

public class day01
{

	public static void main(String[] args)
	{
		Scanner input = new Scanner(System.in);
		int currentElf = 0;
		String line;
		List<Integer> elfCalories = new ArrayList<Integer>();

		while (input.hasNext())
		{
			line = input.nextLine();
			if (line.equals(""))
			{
				elfCalories.add(currentElf);
				currentElf = 0;
			}
			else
				currentElf += Integer.parseInt(line);
		}

		input.close();
		Collections.sort(elfCalories, Collections.reverseOrder());
		System.out.println("part 1: " +  elfCalories.get(0));
		System.out.println("part 2: " + (elfCalories.get(0) + elfCalories.get(1) + elfCalories.get(2)));
	}
}
