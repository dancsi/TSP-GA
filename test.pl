#!/usr/bin/perl -w
use strict;
use SVG;
use List::Util 'max';
use List::Util 'min';

my @ffiles = <tests/*.tsp>;
open(PLOT, ">plot.out");
my (@x, @y, @scaled_x, @scaled_y, $minx, $maxx, $miny, $maxy);
my $svg;


sub read_file
{
	print "reading $_[0]\n";
	open COORDS ,$_[0];
	@x=();
	@y=();
	my $f='';
	while(<COORDS>){ $f .=$_; }
	my $cnt=0;
	while($f =~ /[\d]+[\s]+([-+]?[0-9]*\.?[0-9]+(?:[eE][-+]?[0-9]+)?)[\s]+([-+]?[0-9]*\.?[0-9]+(?:[eE][-+]?[0-9]+)?)/g)
	{
		$x[$cnt]=$1;
		$y[$cnt]=$2;
		#print ("($x[$cnt],$y[$cnt])\n");
		$cnt++;
	}
	$minx=min(@x);
	$maxx=max(@x);
	$miny=min(@y);
	$maxy=max(@y);
	@scaled_x=@x;
	@scaled_y=@y;
	close COORDS;
	#print "done reading\n";
}

sub sqr
{
	return $_[0]*$_[0];
}

sub dist
{
	my $a=$_[0];
	my $b=$_[1];
	return sqrt(sqr($x[$a]-$x[$b])+sqr($y[$a]-$y[$b]));
}

sub path_length
{
	my $ret=0;
	for(my $i=0;$i<$#_;$i++)
	{
		$ret+=dist $_[$i], $_[$i+1];
	}
	return $ret+dist $_[$#_], $_[0];
}

sub create_svg
{
	print "create svg\n";
	my $name=$_[0];
	$maxx-=$minx;
	$maxy-=$miny;
	my $ratio=$maxy/$maxx;
	my $width=400;
	my $height=int(400*$ratio);
	$svg= SVG->new(width=>$width,height=>$height);
	for(my $i=0;$i<=$#x;$i++)
	{
		$scaled_x[$i]-=$minx;
		$scaled_x[$i]=($scaled_x[$i]*$width*0.9/$maxx)+$width*0.05;
		$scaled_y[$i]-=$miny;
		$scaled_y[$i]=($scaled_y[$i]*$height*0.9/$maxy)+$height*0.05;
	}
	open SVGOUT, ">$name";
}

sub draw_cities
{
	my $cities=$svg->group(
        id    => 'cities',
        style => { stroke=>'black', fill=>'black' }
    );
	for(my $i=0;$i<=$#x;$i++)
	{
		$cities->circle(cx=>int($scaled_x[$i]), cy=>int($scaled_y[$i]), r=>2, id=>"city_$i");
	}
}

sub draw_paths1
{
	my $paths=$svg->group(
        id    => 'paths1',
        style => { stroke=>'red', fill=>'red','stroke-width'=>2 }
    );
	my @order=@_;
	my $ntowns=$#order;
	for(my $i=0;$i<$ntowns;$i++)
	{
		$paths->line(id=>"1_$i", x1=>$scaled_x[$order[$i]], y1=>$scaled_y[$order[$i]], x2=>$scaled_x[$order[$i+1]], y2=>$scaled_y[$order[$i+1]]);
	}
	$paths->line(id=>"1_$ntowns", x1=>$scaled_x[$order[$ntowns]], y1=>$scaled_y[$order[$ntowns]], x2=>$scaled_x[$order[0]], y2=>$scaled_y[$order[0]]);
}

sub draw_paths2
{
	my $paths=$svg->group(
        id    => 'paths2',
        style => { stroke=>'blue', fill=>'blue', 'stroke-width'=>1, 'stroke-dasharray'=>'5, 5' }
    );
	my @order=@_;
	my $ntowns=$#order;
	for(my $i=0;$i<$ntowns;$i++)
	{
		$paths->line(id=>"2_$i", x1=>$scaled_x[$order[$i]], y1=>$scaled_y[$order[$i]], x2=>$scaled_x[$order[$i+1]], y2=>$scaled_y[$order[$i+1]]);
	}
	$paths->line(id=>"2_$ntowns", x1=>$scaled_x[$order[$ntowns]], y1=>$scaled_y[$order[$ntowns]], x2=>$scaled_x[$order[0]], y2=>$scaled_y[$order[0]]);
}



my $file;
foreach $file (@ffiles) {
	read_file $file;
	create_svg $file.".svg";
	print "**************************************************************************\n";
	print "Obradjujem ".$file."\n**************************************************************************\n";
	print "MOJ PROGRAM\n";
	system("tsp_benchmark $file 2>NUL 1>NUL");
	open(OUT, "<best.dat");
	my $line;
	while(<OUT>){
		$line.=$_;
	}
	close OUT;
	my @tokens=split(/[: ]+/, $line);
	my $len1= $tokens[$#tokens];
	$#tokens--;
	draw_paths1 @tokens;
	$file =~ m/[a-zA-Z]*([0-9]*)\.tsp/;
	my $ntowns=$1;
	print PLOT "$ntowns $len1 ";
	open(LKH_PAR, ">in.par");
	print LKH_PAR "PROBLEM_FILE = ".$file."\nOUTPUT_TOUR_FILE = best2.dat\n";
	close(LKH_PAR);
	print "DRUGI PROGRAM\n";
	system("echo|lkh>NUL", "in.par");
	open(OUT, "<best2.dat");
	@tokens=();
	my $i=-1;
	while(<OUT>){
		if(m/^(\d+)$/)
		{
			$i++;
			$tokens[$i]=$1-1;
		}
	}
	close OUT;
	#print join("+", @tokens);
	print PLOT path_length(@tokens)."\n";
	draw_paths2 @tokens;
	draw_cities;
	print SVGOUT $svg->xmlify;
	close SVGOUT;
	print "ZAVRSIO SA $file\n\n\n"
} 
 
 close(PLOT);
 open PLOT, "<plot.out";
 my @sorted=sort {($a =~ /(\d+)/)[0] <=> ($b =~ /(\d+)/)[0]} <PLOT>;
 close PLOT;
 open PLOT, ">plot.out";
 print PLOT @sorted;
 close PLOT;