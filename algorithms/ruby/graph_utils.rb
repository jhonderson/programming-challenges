require_relative 'node'
require_relative 'graph'
require_relative 'min_cut'

def read_graph_from_file(p_file_path)
  graph = Graph.new                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
  File.open(p_file_path, "r") do |f|
    f.each_line do |line|
      node_list = line.split("\t")

      # Se remueve el endline
      node_list.pop

      # Se obtiene y remueve el primer elemento (etiqueta del vertice)
      node_label = Integer(node_list.shift)

      node_list.each do |element|
      	graph.add_edge(node_label, Integer(element))
      end
    end
  end
  return graph
end

def find_best_min_cut_n_times(p_graph, p_n_times)
  min_cuts = []
  p_n_times.times do
    temp_graph = p_graph.clone
    min_cuts << min_cut(temp_graph)
  end
  return min_cuts.min
end

file_name = "/home/jhon/workspace/text_files/kargerMinCut.txt"
graph = read_graph_from_file(file_name)
min_cut = find_best_min_cut_n_times(graph, 200)
puts "for #{file_name}, min_cut: #{min_cut}"