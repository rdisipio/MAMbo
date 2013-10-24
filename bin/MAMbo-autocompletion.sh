MAMboAutocompletion()
{
   cur=${COMP_WORDS[COMP_CWORD]}
   case "${cur}" in
      -*)
  	  COMPREPLY=( $( compgen -W '-f --filelist -n --nevents -o --output -p --params' -- $cur ) );;
      --*)
	  COMPREPLY=( $( compgen -W '--filelist --nevents --output --params' -- $cur ) );;
  esac
  return 0
}

complete -o default -o nospace -F MAMboAutocompletion runMAMbo  

