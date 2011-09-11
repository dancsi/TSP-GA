#!/usr/bin/perl -w
use strict;
use SVG;
use List::Util 'max';
use List::Util 'min';

my @ffiles = <tests/*>;
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
		print ("($x[$cnt],$y[$cnt])\n");
		$cnt++;
	}
	$minx=min(@x);
	$maxx=max(@x);
	$miny=min(@y);
	$maxy=max(@y);
	@scaled_x=@x;
	@scaled_y=@y;
	close COORDS;
	print "done reading\n";
}

sub create_svg
{
	my $name=$_[0];
	$maxx-=$minx;
	$maxy-=$miny;
	my $ratio=$maxy/$maxx;
	my $width=400;
	my $height=int(400*$ratio);
	$svg= SVG->new(width=>$width,height=>$height);
	my $cities=$svg->group(
        id    => 'cities',
        style => { stroke=>'black', fill=>'red' }
    );
	for(my $i=0;$i<=$#x;$i++)
	{
		$scaled_x[$i]-=$minx;
		$scaled_x[$i]=($scaled_x[$i]*$width*0.9/$maxx)+$width*0.05;
		$scaled_y[$i]-=$miny;
		$scaled_y[$i]=($scaled_y[$i]*$height*0.9/$maxy)+$height*0.05;
		$cities->circle(cx=>int($scaled_x[$i]), cy=>int($scaled_y[$i]), r=>3, id=>"city_$i");
	}
	open SVGOUT, ">$name";
}

sub draw_paths
{
	my $paths=$svg->group(
        id    => 'paths1',
        style => { stroke=>'blue', fill=>'blue' }
    );
	my @order=@_;
	my $ntowns=@order;
	for(my $i=0;$i<$ntowns;$i++)
	{
		$paths->line(id=>"1_$i", x1=>$scaled_x[$order[$i]], y1=>$scaled_y[$order[$i]], x2=>$scaled_x[$order[$i+1]], y2=>$scaled_y[$order[$i+1]]);
	}
	$paths->line(id=>"1_$ntowns", x1=>$scaled_x[$order[$ntowns]], y1=>$scaled_y[$order[$ntowns]], x2=>$scaled_x[$order[0]], y2=>$scaled_y[$order[0]]);
}

my $file;
foreach $file (@ffiles) {
	read_file $file;
	create_svg $file.".svg";
	print "**************************************************************************\n";
	print "Obradjujem ".$file."\n**************************************************************************\n";
	system("tsp_benchmark", $file);
	open(OUT, "<best.dat");
	my $line;
	while(<OUT>){
		$line.=$_;
	}
	close OUT;
	my @tokens=split(/[: ]+/, $line);
	my $len1= $tokens[$#tokens];
	$#tokens--;
	draw_paths @tokens;
	print SVGOUT $svg->xmlify;
	close SVGOUT;
	$file =~ m/r([0-9]*)\.tsp/;
	my $ntowns=$1;
	print PLOT ($ntowns)." ".$len1;
	open(LKH_PAR, ">in.par");
	print LKH_PAR "PROBLEM_FILE = ".$file."\nOUTPUT_TOUR_FILE = best2.dat\n";
	close(LKH_PAR);
	system("lkh", "in.par");
	<STDIN>;
} 
 
 close(PLOT)